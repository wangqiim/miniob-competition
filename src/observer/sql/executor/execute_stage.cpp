/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Longda on 2021/4/13.
//

#include <string>
#include <sstream>
#include <map>
#include <unordered_set>

#include "execute_stage.h"

#include "common/io/io.h"
#include "common/log/log.h"
#include "common/seda/timer_stage.h"
#include "common/lang/string.h"
#include "session/session.h"
#include "event/storage_event.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "event/execution_plan_event.h"
#include "sql/executor/execution_node.h"
#include "storage/common/table.h"
#include "storage/default/default_handler.h"
#include "storage/common/condition_filter.h"
#include "storage/trx/trx.h"

using namespace common;

RC create_selection_executor(Trx *trx, const Selects &selects, const char *db, const char *table_name, SelectExeNode &select_node);
RC create_join_selection_executor(Trx *trx, const Selects &selects, const char *db, std::vector<TupleSet> &&tuple_sets, JoinExeNode &join_exe_node);
RC create_aggregate_executor(Trx *trx, const Selects &selects, const char *db, const char *table_name, AggregateExeNode &aggregate_node);
RC aggreDesc_check_and_set(Table *table, const Aggregate &aggregate, AggreDesc &aggre_desc);

//! Constructor
ExecuteStage::ExecuteStage(const char *tag) : Stage(tag) {}

//! Destructor
ExecuteStage::~ExecuteStage() {}

//! Parse properties, instantiate a stage object
Stage *ExecuteStage::make_stage(const std::string &tag) {
  ExecuteStage *stage = new (std::nothrow) ExecuteStage(tag.c_str());
  if (stage == nullptr) {
    LOG_ERROR("new ExecuteStage failed");
    return nullptr;
  }
  stage->set_properties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool ExecuteStage::set_properties() {
  //  std::string stageNameStr(stageName);
  //  std::map<std::string, std::string> section = theGlobalProperties()->get(
  //    stageNameStr);
  //
  //  std::map<std::string, std::string>::iterator it;
  //
  //  std::string key;

  return true;
}

//! Initialize stage params and validate outputs
bool ExecuteStage::initialize() {
  LOG_TRACE("Enter");

  std::list<Stage *>::iterator stgp = next_stage_list_.begin();
  default_storage_stage_ = *(stgp++);
  mem_storage_stage_ = *(stgp++);

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void ExecuteStage::cleanup() {
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void ExecuteStage::handle_event(StageEvent *event) {
  LOG_TRACE("Enter\n");

  handle_request(event);

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::callback_event(StageEvent *event, CallbackContext *context) {
  LOG_TRACE("Enter\n");

  // here finish read all data from disk or network, but do nothing here.
  ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
  SQLStageEvent *sql_event = exe_event->sql_event();
  sql_event->done_immediate();

  LOG_TRACE("Exit\n");
  return;
}

RC pre_check(const char *db, Query *sql, SessionEvent *session_event) {
  switch (sql->flag) {
    case SCF_SELECT: {
      // 1. check relation (from, select, where) valid
      Selects selects = sql->sstr.selection;
      std::unordered_set<std::string> from_relation;
      for (int i = 0; i < selects.relation_num; ++i) {
        if (DefaultHandler::get_default().find_table(db, selects.relations[i]) == nullptr) {
          return RC::SCHEMA_TABLE_NOT_EXIST;
        }
        from_relation.insert(selects.relations[i]);
      }
      for (int i = 0; i < selects.attr_num; ++i) {
        if (nullptr != selects.attributes[i].relation_name &&
            from_relation.count(selects.attributes[i].relation_name) == 0) {
          return RC::SCHEMA_TABLE_NOT_EXIST;
        }
      }
      Condition condition;
      for (int i = 0; i < selects.condition_num; ++i) {
        condition = selects.conditions[i];
        if ((condition.left_is_attr && condition.left_attr.relation_name != nullptr && from_relation.count(condition.left_attr.relation_name) == 0)
          || (condition.right_is_attr && condition.right_attr.relation_name != nullptr && from_relation.count(condition.right_attr.relation_name) == 0)) {
          return RC::SCHEMA_TABLE_NOT_EXIST;
        }
      }

      // 2. check attr field (select, where) valid
      for (int i = 0; i < selects.attr_num; ++i) {
        if (selects.attributes[i].attribute_name == nullptr) {
          return RC::SCHEMA_FIELD_NOT_EXIST; 
        }
        // 2.1 relation.attr
        if (nullptr != selects.attributes[i].relation_name) {
          if (strcmp("*", selects.attributes[i].attribute_name) != 0 &&
            DefaultHandler::get_default().find_table(db, selects.relations[i])->table_meta().field(selects.attributes[i].attribute_name) == nullptr) {
            return RC::SCHEMA_FIELD_NOT_EXIST;
          }
        } else {
          // 2.2 attr
          if (strcmp("*", selects.attributes[i].attribute_name) != 0 && selects.relation_num != 0 &&
            DefaultHandler::get_default().find_table(db, selects.relations[0])->table_meta().field(selects.attributes[i].attribute_name) == nullptr) {
            return RC::SCHEMA_FIELD_NOT_EXIST;
          }
        }
      }
      for (int i = 0; i < selects.condition_num; ++i) {
        condition = selects.conditions[i];
        if (condition.left_is_attr == 1) {
          // 2.3 condition: left relation.attr
          if (condition.left_attr.relation_name != nullptr &&
            DefaultHandler::get_default().find_table(db, selects.relations[i])->table_meta().field(condition.left_attr.attribute_name) == nullptr) {
              return RC::SCHEMA_FIELD_NOT_EXIST;
          }
          // 2.3 condition: left attr
          if (condition.left_attr.relation_name == nullptr && selects.relation_num != 0 && 
            DefaultHandler::get_default().find_table(db, selects.relations[0])->table_meta().field(condition.left_attr.attribute_name) == nullptr) {
              return RC::SCHEMA_FIELD_NOT_EXIST;
          }
        }
        if (condition.right_is_attr == 1) {
          // 2.3 condition: right relation.attr
          if (condition.right_attr.relation_name != nullptr &&
            DefaultHandler::get_default().find_table(db, selects.relations[i])->table_meta().field(condition.right_attr.attribute_name) == nullptr) {
              return RC::SCHEMA_FIELD_NOT_EXIST;
          }
          // 2.3 condition: right attr
          if (condition.right_attr.relation_name == nullptr && selects.relation_num != 0 && 
            DefaultHandler::get_default().find_table(db, selects.relations[0])->table_meta().field(condition.right_attr.attribute_name) == nullptr) {
              return RC::SCHEMA_FIELD_NOT_EXIST;
          }
        }
      }
    }
  }
  return RC::SUCCESS;
}

void ExecuteStage::handle_request(common::StageEvent *event) {
  RC rc;
  ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
  SessionEvent *session_event = exe_event->sql_event()->session_event();
  Query *sql = exe_event->sqls();
  const char *current_db = session_event->get_client()->session->get_current_db().c_str();

  CompletionCallback *cb = new (std::nothrow) CompletionCallback(this, nullptr);
  if (cb == nullptr) {
    LOG_ERROR("Failed to new callback for ExecutionPlanEvent");
    exe_event->done_immediate();
    return;
  }
  exe_event->push_callback(cb);

  rc = pre_check(current_db, sql, exe_event->sql_event()->session_event());
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
    exe_event->done_immediate();
    return;
  }

  switch (sql->flag) {
    case SCF_SELECT: { // select
      
      const Selects &selects = sql->sstr.selection;
      // TODO(wq): 目前出现聚集函数时不允许select其他字段(parse中直接过滤了)
      if (selects.aggre_num != 0) {
        rc = do_aggregate(current_db, sql, exe_event->sql_event()->session_event());
      } else {
        rc = do_select(current_db, sql, exe_event->sql_event()->session_event());
      }
      
      if (rc != RC::SUCCESS) {
        session_event->set_response("FAILURE\n");
      }
      exe_event->done_immediate();
    }
    break;

    case SCF_INSERT:
    case SCF_UPDATE:
    case SCF_DELETE:
    case SCF_CREATE_TABLE:
    case SCF_SHOW_TABLES:
    case SCF_DESC_TABLE:
    case SCF_DROP_TABLE:
    case SCF_CREATE_INDEX:
    case SCF_DROP_INDEX: 
    case SCF_LOAD_DATA: {
      StorageEvent *storage_event = new (std::nothrow) StorageEvent(exe_event);
      if (storage_event == nullptr) {
        LOG_ERROR("Failed to new StorageEvent");
        event->done_immediate();
        return;
      }

      default_storage_stage_->handle_event(storage_event);
    }
    break;
    case SCF_SYNC: {
      RC rc = DefaultHandler::get_default().sync();
      session_event->set_response(strrc(rc));
      exe_event->done_immediate();
    }
    break;
    case SCF_BEGIN: {
      session_event->get_client()->session->set_trx_multi_operation_mode(true);
      session_event->set_response(strrc(RC::SUCCESS));
      exe_event->done_immediate();
    }
    break;
    case SCF_COMMIT: {
      Trx *trx = session_event->get_client()->session->current_trx();
      RC rc = trx->commit();
      session_event->get_client()->session->set_trx_multi_operation_mode(false);
      session_event->set_response(strrc(rc));
      exe_event->done_immediate();
    }
    break;
    case SCF_ROLLBACK: {
      Trx *trx = session_event->get_client()->session->current_trx();
      RC rc = trx->rollback();
      session_event->get_client()->session->set_trx_multi_operation_mode(false);
      session_event->set_response(strrc(rc));
      exe_event->done_immediate();
    }
    break;
    case SCF_HELP: {
      const char *response = "show tables;\n"
          "desc `table name`;\n"
          "create table `table name` (`column name` `column type`, ...);\n"
          "create index `index name` on `table` (`column`);\n"
          "insert into `table` values(`value1`,`value2`);\n"
          "update `table` set column=value [where `column`=`value`];\n"
          "delete from `table` [where `column`=`value`];\n"
          "select [ * | `columns` ] from `table`;\n";
      session_event->set_response(response);
      exe_event->done_immediate();
    }
    break;
    case SCF_EXIT: {
      // do nothing
      const char *response = "Unsupported\n";
      session_event->set_response(response);
      exe_event->done_immediate();
    }
    break;
    default: {
      exe_event->done_immediate();
      LOG_ERROR("Unsupported command=%d\n", sql->flag);
    }
  }
}

void end_trx_if_need(Session *session, Trx *trx, bool all_right) {
  if (!session->is_trx_multi_operation_mode()) {
    if (all_right) {
      trx->commit();
    } else {
      trx->rollback();
    }
  }
}

// 这里没有对输入的某些信息做合法性校验，比如查询的列名、where条件中的列名等，没有做必要的合法性校验
// 需要补充上这一部分. 校验部分也可以放在resolve，不过跟execution放一起也没有关系
RC ExecuteStage::do_select(const char *db, Query *sql, SessionEvent *session_event) {

  RC rc = RC::SUCCESS;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  const Selects &selects = sql->sstr.selection;
  // 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
  std::vector<SelectExeNode *> select_nodes;
  for (size_t i = 0; i < selects.relation_num; i++) {
    const char *table_name = selects.relations[i];
    SelectExeNode *select_node = new SelectExeNode;
    rc = create_selection_executor(trx, selects, db, table_name, *select_node);
    if (rc != RC::SUCCESS) {
      delete select_node;
      for (SelectExeNode *& tmp_node: select_nodes) {
        delete tmp_node;
      }
      end_trx_if_need(session, trx, false);
      return rc;
    }
    select_nodes.push_back(select_node);
  }

  if (select_nodes.empty()) {
    LOG_ERROR("No table given");
    end_trx_if_need(session, trx, false);
    return RC::SQL_SYNTAX;
  }

  std::vector<TupleSet> tuple_sets;
  for (SelectExeNode *&node: select_nodes) {
    TupleSet tuple_set;
    rc = node->execute(tuple_set);
    if (rc != RC::SUCCESS) {
      for (SelectExeNode *& tmp_node: select_nodes) {
        delete tmp_node;
      }
      end_trx_if_need(session, trx, false);
      return rc;
    } else {
      tuple_sets.push_back(std::move(tuple_set));
    }
  }

  std::stringstream ss;
  if (tuple_sets.size() > 1) {
    // 本次查询了多张表，需要做join操作
    JoinExeNode join_exe_node;
    create_join_selection_executor(trx, selects, db, std::move(tuple_sets), join_exe_node);
    TupleSet tuple_set;
    join_exe_node.execute(tuple_set);
    tuple_set.print(ss, true);
  } else {
    // 当前只查询一张表，直接返回结果即可
    tuple_sets.front().print(ss);
  }

  for (SelectExeNode *& tmp_node: select_nodes) {
    delete tmp_node;
  }
  session_event->set_response(ss.str());
  end_trx_if_need(session, trx, true);
  return rc;
}

bool match_table(const Selects &selects, const char *table_name_in_condition, const char *table_name_to_match) {
  if (table_name_in_condition != nullptr) {
    return 0 == strcmp(table_name_in_condition, table_name_to_match);
  }

  return selects.relation_num == 1;
}

static RC schema_add_field(Table *table, const char *field_name, TupleSchema &schema) {
  const FieldMeta *field_meta = table->table_meta().field(field_name);
  if (nullptr == field_meta) {
    LOG_WARN("No such field. %s.%s", table->name(), field_name);
    return RC::SCHEMA_FIELD_MISSING;
  }

  schema.add_if_not_exists(field_meta->type(), table->name(), field_meta->name());
  return RC::SUCCESS;
}

// 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
RC create_selection_executor(Trx *trx, const Selects &selects, const char *db, const char *table_name, SelectExeNode &select_node) {
  // 列出跟这张表关联的Attr
  TupleSchema schema;
  Table * table = DefaultHandler::get_default().find_table(db, table_name);
  if (nullptr == table) {
    LOG_WARN("No such table [%s] in db [%s]", table_name, db);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  if (selects.relation_num > 1) { // todo(yqs): 多表查询时，先将所有字段都查询出来，在后续做筛选，其实可以按查询条件先筛选，未必需要全部先查出来
    TupleSchema::from_table(table, schema);
  } else {
    for (int i = selects.attr_num - 1; i >= 0; i--) {
      const RelAttr &attr = selects.attributes[i];
      if (nullptr == attr.relation_name || 0 == strcmp(table_name, attr.relation_name)) {
        if (0 == strcmp("*", attr.attribute_name)) {
          // 列出这张表所有字段
          TupleSchema::from_table(table, schema);
          break; // 没有校验，给出* 之后，再写字段的错误
        } else {
          // 列出这张表相关字段
          RC rc = schema_add_field(table, attr.attribute_name, schema);
          if (rc != RC::SUCCESS) {
            return rc;
          }
        }
      }
    }
  }

  // 找出仅与此表相关的过滤条件, 或者都是值的过滤条件
  std::vector<DefaultConditionFilter *> condition_filters;
  for (size_t i = 0; i < selects.condition_num; i++) {
    const Condition &condition = selects.conditions[i];
    if ((condition.left_is_attr == 0 && condition.right_is_attr == 0) || // 两边都是值
        (condition.left_is_attr == 1 && condition.right_is_attr == 0 && match_table(selects, condition.left_attr.relation_name, table_name)) ||  // 左边是属性右边是值
        (condition.left_is_attr == 0 && condition.right_is_attr == 1 && match_table(selects, condition.right_attr.relation_name, table_name)) ||  // 左边是值，右边是属性名
        (condition.left_is_attr == 1 && condition.right_is_attr == 1 &&
            match_table(selects, condition.left_attr.relation_name, table_name) && match_table(selects, condition.right_attr.relation_name, table_name)) // 左右都是属性名，并且表名都符合
        ) {
      DefaultConditionFilter *condition_filter = new DefaultConditionFilter();
      RC rc = condition_filter->init(*table, condition);
      if (rc != RC::SUCCESS) {
        delete condition_filter;
        for (DefaultConditionFilter * &filter : condition_filters) {
          delete filter;
        }
        return rc;
      }
      condition_filters.push_back(condition_filter);
    }
  }

  return select_node.init(trx, table, std::move(schema), std::move(condition_filters));
}


RC create_join_selection_executor(Trx *trx, const Selects &selects, const char *db, std::vector<TupleSet> &&tuple_sets, JoinExeNode &join_exe_node) {
  // {table_name: table}
  auto table_map = std::make_unique<std::map<std::string, Table*>>();
  // {table_name: (table_index, {value_name: value_index})}
  std::map<std::string, std::pair<int, std::map<std::string, int>>> table_value_index;
  Table *table;
  for (int table_index = 0; table_index < tuple_sets.size(); table_index++) {
    TupleSet &tuple_set = tuple_sets[table_index];
    assert(!tuple_set.get_schema().fields().empty());
    const char *table_name = tuple_set.get_schema().field(0).table_name();
    table = DefaultHandler::DefaultHandler::get_default().find_table(db, table_name);
    if (nullptr == table) {
      LOG_WARN("No such table [%s] in db [%s]", table_name, db);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    table_map->emplace(table_name, table);
    std::map<std::string, int> value_index_map;
    for (int value_index = 0; value_index < tuple_set.get_schema().fields().size(); value_index++) {
      const TupleField & tuple_field = tuple_set.get_schema().field(value_index);
      value_index_map.emplace(tuple_field.field_name(), value_index);
    }
    table_value_index.emplace(table_name, std::pair<int, std::map<std::string, int>>{table_index, value_index_map});
  }
  // 构造多表查询返回schema
  TupleSchema schema;
  if (selects.attr_num == 1 // select * from t1, t2
    && nullptr == selects.attributes[0].relation_name
    && strcmp("*", selects.attributes[0].attribute_name) == 0 ) {
    for (int i = selects.relation_num -1; i >= 0; --i) {
      auto find_table = table_map->find(selects.relations[i]);
      TupleSchema::from_table(find_table->second, schema);
    }
  } else {
    for (int i = selects.attr_num - 1; i >= 0; i--) {
      const RelAttr &attr = selects.attributes[i];
      // todo(yqs): 前置校验项，对于多表查询，必须指定relation_name
      assert(nullptr != attr.relation_name);
      auto find_table = table_map->find(attr.relation_name);
      // todo(yqs): 前置校验项，relation_name必须存在，且必须存在于selects.relations
      assert(find_table != table_map->end());
      if (0 == strcmp("*", attr.attribute_name)) {
        TupleSchema::from_table(find_table->second, schema);
      } else {
        RC rc = schema_add_field(find_table->second, attr.attribute_name, schema);
        if (rc != RC::SUCCESS) {
          return rc;
        }
      }
    }
  }

  // 找出仅与此表相关的过滤条件, 或者都是值的过滤条件
  std::vector<DefaultInnerJoinFilter *> condition_filters;
  for (size_t i = 0; i < selects.condition_num; i++) {
    const Condition &condition = selects.conditions[i];
    if (condition.left_is_attr == 1 && condition.right_is_attr == 1) { // 两边都是属性的condition才需要做联表查询
      // left condition
      auto find_left_table = table_value_index.find(condition.left_attr.relation_name);
      assert(find_left_table != table_value_index.end());
      int left_table_index = find_left_table->second.first;
      auto find_left_value = find_left_table->second.second.find(condition.left_attr.attribute_name);
      assert(find_left_value != find_left_table->second.second.end());
      int left_value_index = find_left_value->second;
      JoinConDesc left_cond{left_table_index, left_value_index};
      // right condition
      auto find_right_table = table_value_index.find(condition.right_attr.relation_name);
      assert(find_right_table != table_value_index.end());
      int right_table_index = find_right_table->second.first;
      auto find_right_value = find_right_table->second.second.find(condition.right_attr.attribute_name);
      assert(find_right_value != find_right_table->second.second.end());
      int right_value_index = find_right_value->second;
      JoinConDesc right_cond{right_table_index, right_value_index};
      // build condition
      auto *condition_filter = new DefaultInnerJoinFilter();
      condition_filter->init(left_cond, right_cond, condition.comp);

      condition_filters.push_back(condition_filter);
    }
  }
  auto *condition_filter = new CompositeJoinFilter();
  condition_filter->init(std::move(condition_filters), condition_filters.size());

  return join_exe_node.init(trx, std::move(tuple_sets),
                            std::move(schema),
                            condition_filter,
                            std::move(table_value_index));
}
RC ExecuteStage::do_aggregate(const char *db, Query *sql, SessionEvent *session_event) {

  RC rc = RC::SUCCESS;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  const Selects &selects = sql->sstr.selection;
  // 目前聚集函数仅仅支持单表
  if (selects.relation_num != 1) {
    LOG_INFO("aggregate function only support single relation");
    return RC::INVALID_ARGUMENT;
  }
  const char *table_name = selects.relations[0];

  AggregateExeNode *aggregate_node = new AggregateExeNode;
  rc = create_aggregate_executor(trx, selects, db, table_name, *aggregate_node);
  if (rc != RC::SUCCESS) {
    delete aggregate_node;
    end_trx_if_need(session, trx, false);
    return rc;
  }
  
  AggreSet aggreset;
  rc = aggregate_node->execute(aggreset);
  if (rc != RC::SUCCESS) {
    delete aggregate_node;
    end_trx_if_need(session, trx, false);
    return rc;
  }
  // 聚集空记录时直接返回FAILURE
  rc = aggreset.finish_aggregate();
  if (rc != RC::SUCCESS) {
    delete aggregate_node;
    end_trx_if_need(session, trx, false);
    return rc;
  }
  std::stringstream ss;
  aggreset.print(ss);

  session_event->set_response(ss.str());
  end_trx_if_need(session, trx, true);

  delete aggregate_node;
  return rc;
}

// 生成最底层的aggregate 执行节点,
RC create_aggregate_executor(Trx *trx, const Selects &selects, const char *db, const char *table_name, AggregateExeNode &aggregate_node) {
  RC rc = RC::SUCCESS;
  Table *table = DefaultHandler::get_default().find_table(db, table_name);
  if (nullptr == table) {
    LOG_WARN("No such table [%s] in db [%s]", table_name, db);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  std::vector<AggreDesc *> aggre_descs;
  // 枚举所有聚集函数
  for (int i = 0; i < selects.aggre_num; i++) {
    AggreDesc *aggre_desc = new AggreDesc;
    if (RC::SUCCESS != aggreDesc_check_and_set(table, selects.aggregates[i], *aggre_desc)) {
      delete aggre_desc;
      for (AggreDesc *& tmp_aggreDesc : aggre_descs) {
        delete tmp_aggreDesc;
      }
      return RC::INVALID_ARGUMENT;
    }
    // 是属性时，属性是否存在，类型是否合法
    // 属性是值时，检验是否是*,只有
    aggre_descs.push_back(aggre_desc);
  }

  // 找出仅与此表相关的过滤条件, 或者都是值的过滤条件
  std::vector<DefaultConditionFilter *> condition_filters;
  for (size_t i = 0; i < selects.condition_num; i++) {
    const Condition &condition = selects.conditions[i];
    if ((condition.left_is_attr == 0 && condition.right_is_attr == 0) || // 两边都是值
        (condition.left_is_attr == 1 && condition.right_is_attr == 0 && match_table(selects, condition.left_attr.relation_name, table_name)) ||  // 左边是属性右边是值
        (condition.left_is_attr == 0 && condition.right_is_attr == 1 && match_table(selects, condition.right_attr.relation_name, table_name)) ||  // 左边是值，右边是属性名
        (condition.left_is_attr == 1 && condition.right_is_attr == 1 &&
            match_table(selects, condition.left_attr.relation_name, table_name) && match_table(selects, condition.right_attr.relation_name, table_name)) // 左右都是属性名，并且表名都符合
        ) {
      DefaultConditionFilter *condition_filter = new DefaultConditionFilter();
      RC rc = condition_filter->init(*table, condition);
      if (rc != RC::SUCCESS) {
        delete condition_filter;
        for (DefaultConditionFilter * &filter : condition_filters) {
          delete filter;
        }
        return rc;
      }
      condition_filters.push_back(condition_filter);
    }
  }

  return aggregate_node.init(trx, table, std::move(aggre_descs), std::move(condition_filters));
}

// 目前不考虑aggre(t.*)的情况, 以及 aggre("as"),仅可能"aggre(attr1),其中attr1是字符串属性
RC aggreDesc_check_and_set(Table *table, const Aggregate &aggregate, AggreDesc &aggre_desc) {
  aggre_desc.aggre_type = aggregate.aggre_type;
  aggre_desc.is_attr = aggregate.is_attr;
  aggre_desc.is_star = 0;
  if (aggregate.is_attr == 1) {
    // 属性：检验字段和表名
    aggre_desc.relation_name = aggregate.attr.relation_name;
    if (nullptr == aggregate.attr.relation_name || 0 == strcmp(table->name(), aggregate.attr.relation_name)) {
      // 如果表明不为空则表明需要匹配上
      if (aggregate.attr.attribute_name != 0 && 0 == strcmp("*", aggregate.attr.attribute_name)) {
        if (aggregate.aggre_type != AggreType::COUNTS) {
          // 只有COUNT能匹配*
          return RC::SCHEMA_FIELD_MISSING;
        }
        // 把*当作值"1",来处理，但是依然需要记录属性名为*，方便最后输出表头
        aggre_desc.attr_name = aggregate.attr.attribute_name;
        aggre_desc.is_attr = 0;
        aggre_desc.is_star = 1;
        aggre_desc.value = 1;
        return RC::SUCCESS;
      }
      
      // 检验聚合属性是否合法
      const FieldMeta *field_meta = table->table_meta().field(aggregate.attr.attribute_name);
      if (nullptr == field_meta) {
        return RC::SCHEMA_FIELD_MISSING;
      }
      // 只能对float和int和char字段进行聚集
      // 不考虑聚合date
      if (field_meta->type() != AttrType::INTS && field_meta->type() != AttrType::FLOATS && field_meta->type() != AttrType::CHARS) {
        return RC::SCHEMA_FIELD_MISSING;
      }
      // char属性不能进行 sum 和 avg 聚合
      if (field_meta->type() == AttrType::CHARS && (aggregate.aggre_type == AggreType::SUMS || aggregate.aggre_type == AggreType::AVGS)) {
        return RC::SCHEMA_FIELD_MISSING;
      }
      aggre_desc.attr_name = const_cast<char *>(field_meta->name());
    } else {
      // 表名不匹配: example: t.id, t却不存在
      return RC::SCHEMA_FIELD_MISSING;
    }
  } else {
    // 不考虑aggregate("asd")的情况
    if (aggregate.value.type == AttrType::INTS) {
      aggre_desc.value = *((int *)(aggregate.value.data));
    } else if(aggregate.value.type == AttrType::FLOATS) {
      aggre_desc.value = *((float *)(aggregate.value.data));
    } else {
      return RC::SCHEMA_FIELD_MISSING;
    }
  }
  return RC::SUCCESS;
}
