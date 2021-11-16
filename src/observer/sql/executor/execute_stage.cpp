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
#include "sql/executor/aggregate_execution_node.h"
#include "storage/common/table.h"
#include "storage/default/default_handler.h"
#include "storage/common/condition_filter.h"
#include "storage/trx/trx.h"
#include "executor.h"
#include "executor_builder.h"

using namespace common;

RC create_field_index(const Selects &selects, const char *db, std::map<std::string, std::map<std::string, int>> &field_index);
RC create_selection_executor(Trx *trx, const Selects &selects, const char *db, const char *table_name, SelectExeNode &select_node);
RC create_cartesian_executor(Trx *trx, const Selects &selects, const char *db, std::vector<TupleSet> &&tuple_sets, 
                              cartesianExeNode &cartesian_exe_node, const std::map<std::string, std::map<std::string, int>> &field_index);
RC create_orderby_executor(Trx *trx, const Selects &selects, const char *db, OrderByExeNode &order_by_exe_node,
                            const std::map<std::string, std::map<std::string, int>> &field_index);
RC create_aggregation_executor(Trx *trx, const Selects &selects, const char *db, TupleSet &&tuple_set, AggregationExeNode &aggregation_node,
                                const std::map<std::string, std::map<std::string, int>> &field_indexs);
RC create_output_executor(Trx *trx, const Selects &selects, const char *db, TupleSet &&tuple_set, OutputExeNode &output_node,
                            const std::map<std::string, std::map<std::string, int>> &field_index);
RC aggreDesc_check_and_set(const Aggregate &aggregate, AggreDesc &aggre_desc,
                            const std::map<std::string, std::map<std::string, int>> &field_index);

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
      std::unordered_set<std::string> all_relation;
      for (int i = 0; i < selects.relation_num; ++i) {
        if (DefaultHandler::get_default().find_table(db, selects.relations[i]) == nullptr) {
          return RC::SCHEMA_TABLE_NOT_EXIST;
        }
        all_relation.insert(selects.relations[i]);
      }
      for (int i = 0; i < selects.join_num; ++i) {
        Join join = selects.joins[i];
        if (DefaultHandler::get_default().find_table(db, join.table_name) == nullptr) {
          return RC::SCHEMA_TABLE_NOT_EXIST;
        }
        all_relation.insert(join.table_name);
        for (int j = 0; j < join.condition_num; ++j) {
          Condition join_condition = join.conditions[j];
          if (join_condition.left_is_attr && (join_condition.left_attr.relation_name==nullptr || all_relation.count(join_condition.left_attr.relation_name) == 0)) {
            return RC::SCHEMA_TABLE_NOT_EXIST;
          }
          if (join_condition.right_is_attr && (join_condition.right_attr.relation_name==nullptr || all_relation.count(join_condition.right_attr.relation_name) == 0)) {
            return RC::SCHEMA_TABLE_NOT_EXIST;
          }
        }
      }
      for (int i = 0; i < selects.attr_num; ++i) {
        if (nullptr != selects.attributes[i].relation_name &&
            all_relation.count(selects.attributes[i].relation_name) == 0) {
          return RC::SCHEMA_TABLE_NOT_EXIST;
        }
      }
      Condition condition;
      for (int i = 0; i < selects.condition_num; ++i) {
        condition = selects.conditions[i];
        if ((condition.left_is_attr && condition.left_attr.relation_name != nullptr && all_relation.count(condition.left_attr.relation_name) == 0)
        || (condition.right_is_attr && condition.right_attr.relation_name != nullptr && all_relation.count(condition.right_attr.relation_name) == 0)) {
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
          DefaultHandler::get_default().find_table(db, selects.attributes[i].relation_name)->table_meta().field(selects.attributes[i].attribute_name) == nullptr) {
            return RC::SCHEMA_FIELD_NOT_EXIST;
          }
        } else {
          // 2.2 attr
          if (strcmp("*", selects.attributes[i].attribute_name) != 0) {
            // attr not exist in from table
            if (selects.relation_num == 1 &&
            DefaultHandler::get_default().find_table(db, selects.relations[0])->table_meta().field(selects.attributes[i].attribute_name) == nullptr) {
              return RC::SCHEMA_FIELD_NOT_EXIST;
            }
            // not allow:  select id from t1 ,t2;
            if (selects.relation_num > 1) {
              return RC::SCHEMA_FIELD_NOT_EXIST;
            }
          }
        }
      }
      for (int i = 0; i < selects.condition_num; ++i) {
        condition = selects.conditions[i];
        if (condition.left_is_attr == 1) {
          // 2.3.1 condition left: relation.attr
          if (condition.left_attr.relation_name != nullptr) {
            if (DefaultHandler::get_default().find_table(db, condition.left_attr.relation_name)->table_meta().field(condition.left_attr.attribute_name) == nullptr) {
              return RC::SCHEMA_FIELD_NOT_EXIST;
            }
          } else {
            // left attr (attr must in from relation)
            if (selects.relation_num == 1 &&
            DefaultHandler::get_default().find_table(db, selects.relations[0])->table_meta().field(condition.left_attr.attribute_name) == nullptr) {
              return RC::SCHEMA_FIELD_NOT_EXIST;
            }
            // not allow:  select XX.XX from t1 ,t2 from a op b; a and b must have relation_name
            if (selects.relation_num > 1) {
              return RC::SCHEMA_FIELD_NOT_EXIST;
            }
          }
        }
        if (condition.right_is_attr == 1) {
          // 2.3.2 condition right: relation.attr
          if (condition.right_attr.relation_name != nullptr) {
            if (DefaultHandler::get_default().find_table(db, condition.right_attr.relation_name)->table_meta().field(condition.right_attr.attribute_name) == nullptr) {
              return RC::SCHEMA_FIELD_NOT_EXIST;
            }
          } else {
            // right attr (attr must in from relation)
            if (selects.relation_num == 1 &&
            DefaultHandler::get_default().find_table(db, selects.relations[0])->table_meta().field(condition.right_attr.attribute_name) == nullptr) {
              return RC::SCHEMA_FIELD_NOT_EXIST;
            }
            // not allow:  select XX.XX from t1 ,t2 from a op b; a and b must have relation_name
            if (selects.relation_num > 1) {
              return RC::SCHEMA_FIELD_NOT_EXIST;
            }
          }
        }
      } // attr condition check
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
      if (selects.order_num > 0 || selects.group_num > 0) {
        rc = do_select(current_db, sql, exe_event->sql_event()->session_event());
      } else {
        rc = do_select_v2(current_db, sql, exe_event->sql_event()->session_event());
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
// 流程:selectnode->cartesiannode(如果需要)->orderbynode(如果需要)->aggregatenode(如果需要)->outputnode
RC ExecuteStage::do_select(const char *db, Query *sql, SessionEvent *session_event) {

  RC rc = RC::SUCCESS;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  const Selects &selects = sql->sstr.selection;
  // 1. 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
  std::vector<SelectExeNode *> select_nodes;
  for (int i = selects.relation_num - 1; i >= 0; i--) {
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
  // 执行所有的selectNode,生成每个"表"的结果集
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

  for (SelectExeNode *& tmp_node: select_nodes) {
    delete tmp_node;
  }

  std::stringstream ss;
  // {table_name: {field: value_index})}
  std::map<std::string, std::map<std::string, int>> field_index;
  rc = create_field_index(selects, db, field_index);
  assert(rc == RC::SUCCESS);

  bool is_multi_table = (tuple_sets.size() > 1);
  
  TupleSet tmp_tuple_set;

  // 2. 如果本次查询了多张表，需要做Cartesian操作，合并成一个TupleSet
  if (is_multi_table) {
    cartesianExeNode cartesian_exe_node;
    rc = create_cartesian_executor(trx, selects, db, std::move(tuple_sets), cartesian_exe_node, field_index);
    assert(rc == RC::SUCCESS);
    cartesian_exe_node.execute(tmp_tuple_set);
  } else {
    tmp_tuple_set = std::move(tuple_sets.front());
  }
  // 3. aggregate node
  if (selects.aggre_num != 0) {
    AggregationExeNode aggregationExeNode;
    rc = create_aggregation_executor(trx, selects, db, std::move(tmp_tuple_set), aggregationExeNode, field_index);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    aggregationExeNode.execute(tmp_tuple_set);
    // 此时的tmp_tuple_set可以直接打印了
    tmp_tuple_set.print(ss, is_multi_table);
  } else {
    // 暂不支持 group-by之后进行排序
    // 4. order-by node
    if (selects.order_num != 0) {
      OrderByExeNode orderByExeNode;
      rc = create_orderby_executor(trx, selects, db, orderByExeNode, field_index);
      assert(rc == RC::SUCCESS);
      orderByExeNode.execute(tmp_tuple_set);
    }
    // 5. 生成输出tupleset
    OutputExeNode outputExeNode;
    rc = create_output_executor(trx, selects, db, std::move(tmp_tuple_set), outputExeNode, field_index);
    assert(rc == RC::SUCCESS);
    TupleSet output_tuple_set;
    outputExeNode.execute(output_tuple_set);

    output_tuple_set.print(ss, is_multi_table);
  }
  session_event->set_response(ss.str());
  end_trx_if_need(session, trx, true);
  return rc;
}


RC ExecuteStage::do_select_v2(const char *db, Query *sql, SessionEvent *session_event) {
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  auto executor_builder = new ExecutorBuilder(db, sql, session_event);
  Executor *executor = executor_builder->build();
  assert(executor != nullptr);
  TupleSet result;
  RC rc = executor->init();
  if (rc != RC::SUCCESS) {
    delete executor_builder;
    delete executor;
    end_trx_if_need(session, trx, false);
    return rc;
  }
  rc = executor->next(result);
  if (rc != RC::SUCCESS) {
    delete executor_builder;
    delete executor;
    end_trx_if_need(session, trx, false);
    return rc;
  }
  std::stringstream ss;
  bool multi_table = (sql->sstr.selection.relation_num > 1) || (sql->sstr.selection.join_num > 0);
  result.print(ss, multi_table);
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

static RC schema_add_field(Table *table, const char *field_name, TupleSchema &schema, int order = 0) {
  const FieldMeta *field_meta = table->table_meta().field(field_name);
  if (nullptr == field_meta) {
    LOG_WARN("No such field. %s.%s", table->name(), field_name);
    return RC::SCHEMA_FIELD_MISSING;
  }

  schema.add_if_not_exists(field_meta->type(), table->name(), field_meta->name(), order);
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

  // 保留全部attr,后续可能用来agg或sort,最后才构造ouput schema
  TupleSchema::from_table(table, schema);

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

RC create_field_index(const Selects &selects, const char *db, 
                      std::map<std::string, std::map<std::string, int>> &field_index) {
  int fields_num = 0;
  for (int i = selects.relation_num - 1; i >= 0; --i) {
    field_index[selects.relations[i]] = {};
    Table *table = DefaultHandler::get_default().find_table(db, selects.relations[i]);
    for (int j = table->table_meta().sys_field_num(); j < table->table_meta().field_num(); j++) {
      field_index[selects.relations[i]][table->table_meta().field(j)->name()] = fields_num + j - table->table_meta().sys_field_num();
    }
    fields_num += table->table_meta().field_num() - table->table_meta().sys_field_num();
  }
  return RC::SUCCESS;
}

RC create_cartesian_executor(Trx *trx, const Selects &selects, const char *db, std::vector<TupleSet> &&tuple_sets, 
                            cartesianExeNode &cartesian_exe_node, const std::map<std::string, std::map<std::string, int>> &field_index) {
  // 找出仅与此表相关的过滤条件, 或者都是值的过滤条件
  std::vector<DefaultCartesianFilter *> condition_filters;
  for (size_t i = 0; i < selects.condition_num; i++) {
    const Condition &condition = selects.conditions[i];
    if (condition.left_is_attr == 1 && condition.right_is_attr == 1) { // 两边都是属性的condition才需要做联表查询
      // left condition
      CartesianConDesc left_cond{-1, field_index.at(condition.left_attr.relation_name).at(condition.left_attr.attribute_name)};
      // right condition
      CartesianConDesc right_cond{-1, field_index.at(condition.right_attr.relation_name).at(condition.right_attr.attribute_name)};
      // build condition
      auto *condition_filter = new DefaultCartesianFilter();
      condition_filter->init(left_cond, right_cond, condition.comp);

      condition_filters.push_back(condition_filter);
    }
  }
  auto *condition_filter = new CompositeCartesianFilter();
  condition_filter->init(std::move(condition_filters), condition_filters.size());

  Table *table = nullptr;
  TupleSchema cartesian_schema;
  // 注意：这里构造cartesian_schema的表的顺序一定要和创建selectNode时候遍历表的顺序一致!!!!!
  for (int i = selects.relation_num - 1; i >= 0; i--) {
    table = DefaultHandler::DefaultHandler::get_default().find_table(db, selects.relations[i]);
    assert(table != nullptr);
    TupleSchema::from_table(table, cartesian_schema);
  }
  
  return cartesian_exe_node.init(trx, std::move(tuple_sets), condition_filter, std::move(cartesian_schema));
}

RC create_orderby_executor(Trx *trx, const Selects &selects, const char *db, OrderByExeNode &order_by_exe_node,
                            const std::map<std::string, std::map<std::string, int>> &field_index) {
  TupleSchema order_by_schema;
  Table *table;
  for (size_t i = 0; i < selects.order_num; i++) {
    const RelAttr &attr = selects.order_by[i].attribute;
    if (attr.relation_name != nullptr) {
      table = DefaultHandler::DefaultHandler::get_default().find_table(db, attr.relation_name);
    } else {
      table = DefaultHandler::DefaultHandler::get_default().find_table(db, selects.relations[0]);
    }
    // todo(wq): 前置校验
    if (nullptr == table) {
      LOG_ERROR("No such table [%s] in db [%s]", attr.relation_name, db);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    RC rc = schema_add_field(table, attr.attribute_name, order_by_schema, selects.order_by[i].order);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }
  return order_by_exe_node.init(trx, std::move(order_by_schema), field_index);                    
}


RC create_output_executor(Trx *trx, const Selects &selects, const char *db,
                          TupleSet &&tuple_set, OutputExeNode &output_node,
                          const std::map<std::string, std::map<std::string, int>> &field_index) {
  // 1. 构造结果返回schema  
  TupleSchema output_schema;
  Table *table;
  std::map<std::string, Table*> table_map;
  for (int i = 0; i < selects.relation_num; i++) {
    table = DefaultHandler::DefaultHandler::get_default().find_table(db, selects.relations[i]);
    assert(table != nullptr);
    table_map[selects.relations[i]] = table;
  }
  
  if (selects.relation_num == 1) {
    // 构造单表查询返回schema
    const char *table_name = selects.relations[0];
    for (int i = selects.attr_num - 1; i >= 0; i--) {
      const RelAttr &attr = selects.attributes[i];
      if (nullptr == attr.relation_name || 0 == strcmp(table_name, attr.relation_name)) {
        if (0 == strcmp("*", attr.attribute_name)) {
          // 列出这张表所有字段
          TupleSchema::from_table(table, output_schema);
          break; // 没有校验，给出* 之后，再写字段的错误
        } else {
          // 列出这张表相关字段
          RC rc = schema_add_field(table, attr.attribute_name, output_schema);
          if (rc != RC::SUCCESS) {
            return rc;
          }
        }
      }
    }
  } else {
    // 构造多表查询返回schema
    if (selects.attr_num == 1 // select * from t1, t2
      && nullptr == selects.attributes[0].relation_name
      && strcmp("*", selects.attributes[0].attribute_name) == 0 ) {
      for (int i = selects.relation_num -1; i >= 0; --i) {
        TupleSchema::from_table(table_map[selects.relations[i]], output_schema);
      }
    } else {
      for (int i = selects.attr_num - 1; i >= 0; i--) {
        const RelAttr &attr = selects.attributes[i];
        // todo(yqs): 前置校验项，对于多表查询，必须指定relation_name
        assert(nullptr != attr.relation_name);
        auto find_table = table_map.find(attr.relation_name);
        // todo(yqs): 前置校验项，relation_name必须存在，且必须存在于selects.relations
        assert(find_table != table_map.end());
        if (0 == strcmp("*", attr.attribute_name)) {
          TupleSchema::from_table(find_table->second, output_schema);
        } else {
          RC rc = schema_add_field(find_table->second, attr.attribute_name, output_schema);
          if (rc != RC::SUCCESS) {
            return rc;
          }
        }
      }
    }
  }
  return output_node.init(trx, std::move(output_schema), std::move(tuple_set), field_index);
}

// todo(wq):需要前置校验
// 目前不考虑aggre(t.*)的情况, 以及 aggre("as"),仅可能"aggre(attr1),其中attr1是字符串属性
RC aggreDesc_check_and_set(const Selects &selects, const char *db, const Aggregate &aggregate, AggreDesc &aggre_desc,
                            const std::map<std::string, std::map<std::string, int>> &field_index) {
  aggre_desc.aggre_type = aggregate.aggre_type;
  aggre_desc.is_attr = aggregate.is_attr;
  aggre_desc.is_star = 0;
  if (aggregate.is_attr == 1) {
    // 属性：检验字段和表名
    aggre_desc.relation_name = aggregate.attr.relation_name;
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

    // 检验聚合表和属性是否合法
    const FieldMeta *field_meta = nullptr;
    Table * table = nullptr;
    if (aggregate.attr.relation_name == nullptr) {
      table = DefaultHandler::get_default().find_table(db, selects.relations[0]);
    } else {
      table = DefaultHandler::get_default().find_table(db, aggregate.attr.relation_name);
    }
    assert(table != nullptr);
    field_meta = table->table_meta().field(aggregate.attr.attribute_name);
    if (nullptr == field_meta) {
      return RC::SCHEMA_FIELD_MISSING;
    }
    // 对float和int和char和date字段进行聚集
    if (field_meta->type() == AttrType::UNDEFINED) {
      return RC::SCHEMA_FIELD_MISSING;
    }
    // char和date字段不能进行 sum 和 avg 聚合
    if ((field_meta->type() == AttrType::CHARS || field_meta->type() == AttrType::DATES)
        && (aggregate.aggre_type == AggreType::SUMS || aggregate.aggre_type == AggreType::AVGS)) {
      return RC::SCHEMA_FIELD_MISSING;
    }
    aggre_desc.attr_name = const_cast<char *>(field_meta->name());
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

// 生成最底层的aggregate 执行节点,
RC create_aggregation_executor(Trx *trx, const Selects &selects, const char *db, TupleSet &&tuple_set, AggregationExeNode &aggregation_node,
                                const std::map<std::string, std::map<std::string, int>> &field_index) {
  std::vector<std::shared_ptr<AggreDesc>> aggre_descs;
  // 枚举所有聚集函数
  for (int i = 0; i < selects.aggre_num; i++) {
    std::shared_ptr<AggreDesc> aggre_desc(new AggreDesc());
    if (RC::SUCCESS != aggreDesc_check_and_set(selects, db, selects.aggregates[i], *aggre_desc, field_index)) {
      return RC::INVALID_ARGUMENT;
    }
    // 是属性时，属性是否存在，类型是否合法
    // 属性是值时，检验是否是*,只有
    aggre_descs.emplace_back(std::move(aggre_desc));
  }
  Table *table = DefaultHandler::get_default().find_table(db, selects.relations[0]);
  TupleSchema group_bys;
  for (int i = 0; i < selects.group_num; i++) {
    if (selects.group_bys[i].relation_name == nullptr) {
      TupleSchema::schema_add_field(table ,selects.group_bys[i].attribute_name, group_bys);
    } else {
      Table *t = DefaultHandler::get_default().find_table(db, selects.group_bys[i].relation_name);
      TupleSchema::schema_add_field(t ,selects.group_bys[i].attribute_name, group_bys);
    }
  }
  group_bys.Set_agg_descs(std::move(aggre_descs));
  return aggregation_node.init(trx, table, std::move(group_bys), std::move(tuple_set));
}
