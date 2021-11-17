//
// Created by emrick on 2021/10/31.
//

#include "executor_builder.h"
#include "nest_loop_join_executor.h"
#include "agg_executor.h"

Executor* ExecutorBuilder::build() {
  return build(&sql_->sstr.selection);
}

Executor* ExecutorBuilder::build(Selects *selects) {
  Executor *select_executor = build_select_executor(selects);
  Executor *executor = build_join_executor(select_executor, selects);

  if (selects->aggre_num != 0) {
    TupleSchema output_schema;
    AggExecutor::build_agg_output_schema(db_, selects, output_schema);
    executor = new AggExecutor(new ExecutorContext(), output_schema, executor);
  } else {
    executor->set_output_schema(build_output_schema(selects));
  }
  return executor;
}

TupleSchema ExecutorBuilder::build_output_schema(Selects *selects) {
  TupleSchema output_schema;
  assert(selects->aggre_num == 0); // agg另外建立executor进行处理
  if (selects->attr_num == 1 // select * from t1, t2
  && nullptr == selects->attributes[0].relation_name
  && strcmp("*", selects->attributes[0].attribute_name) == 0 ) {
    for (int i = selects->relation_num - 1; i >= 0; --i) {
      TupleSchema::from_table(db_->find_table(selects->relations[i]), output_schema);
    }
    for (int j = 0; j < selects->join_num; j++) {
      TupleSchema::from_table(db_->find_table(selects->joins[j].table_name), output_schema);
    }
  } else {
    for (int i = selects->attr_num - 1; i >= 0; i--) {
      RelAttr &attr = selects->attributes[i];
      // 前置校验项，对于多表查询，必须指定relation_name
      if (attr.relation_name == NULL) {
        attr.relation_name = selects->relations[0];
      }
      Table *table = db_->find_table(attr.relation_name);
      if (0 == strcmp("*", attr.attribute_name)) {
        TupleSchema::from_table(table, output_schema);
      } else {
        TupleSchema::schema_add_field(table, attr.attribute_name, output_schema);
      }
    }
  }
  return output_schema;
}


/**
 * 只关注select {attrs} from {tables} where {conditions}, 该查询主要作为其他查询的基础
 * 此时仅关注与{tables}相关的{conditions}
 * 而不考虑：join
 * @return
 */
Executor* ExecutorBuilder::build_select_executor(Selects *selects) {
  assert(selects->relation_num > 0);
  auto *context = new ExecutorContext();
  Table *table = DefaultHandler::get_default().find_table(db_->name(), selects->relations[selects->relation_num-1]);
  TupleSchema output_schema0;
  TupleSchema::from_table(table, output_schema0);
  std::vector<Filter*> filters0;
  bool ban_all0 = false;
  Filter::from_condition(selects->conditions, selects->condition_num, table, filters0, ban_all0, false, db_);
  Executor *left_executor = new ScanExecutor(context, table, output_schema0, std::move(filters0), ban_all0);
  Executor *right_executor;

  for (int i = selects->relation_num-2; i >= 0; --i) {
    table = DefaultHandler::get_default().find_table(db_->name(), selects->relations[i]);
    TupleSchema output_schema;
    TupleSchema::from_table(table, output_schema);
    std::vector<Filter*> filters;
    bool ban_all = false;
    Filter::from_condition(selects->conditions, selects->condition_num, table, filters, ban_all, false, db_);
    right_executor = new ScanExecutor(context, table, output_schema, std::move(filters), ban_all);

    TupleSchema join_output_schema;
    join_output_schema.append(left_executor->output_schema());
    join_output_schema.append(right_executor->output_schema());
    std::vector<Filter*> join_filters;
    Filter::from_condition(selects->conditions, selects->condition_num, nullptr, join_filters, ban_all, true, db_);
    left_executor = new NestLoopJoinExecutor(context, join_output_schema, left_executor, right_executor, join_filters, ban_all);
  }
  left_executor = build_sub_query_executor(left_executor, selects->relations[0], selects->conditions, selects->condition_num);
  return left_executor;
}

/**
 * 仅考虑selects中的inner join查询
 * @param executor
 * @param selects
 * @return
 */
Executor* ExecutorBuilder::build_join_executor(Executor *executor, Selects *selects) {
  assert(executor);
  Table *table;
  auto *context = new ExecutorContext();

  Executor *left_executor = executor;
  Executor *right_executor = nullptr;
  for (int i = 0; i < selects->join_num; ++i) {
    table = DefaultHandler::get_default().find_table(db_->name(), selects->joins[i].table_name);
    TupleSchema output_schema;
    TupleSchema::from_table(table, output_schema);
    std::vector<Filter*> filters;
    bool ban_all = false;
    Filter::from_condition(selects->joins[i].conditions, selects->joins[i].condition_num, table, filters, ban_all, false, db_);
    if (!ban_all) {
      Filter::from_condition(selects->conditions, selects->condition_num, table, filters, ban_all, false, db_);
    }
    right_executor = new ScanExecutor(context, table, output_schema, std::move(filters), ban_all);

    TupleSchema join_output_schema;
    join_output_schema.append(left_executor->output_schema());
    join_output_schema.append(right_executor->output_schema());
    std::vector<Filter*> join_filters;
    Filter::from_condition(selects->joins[i].conditions, selects->joins[i].condition_num, nullptr, join_filters, ban_all, true, db_);
    if (i == 0 && !ban_all) { // 对于最后一个join，需要对join_condition和selects->condition中的条件一起进行过滤
      Filter::from_condition(selects->conditions, selects->condition_num, nullptr, join_filters, ban_all, true, db_);
    }
    left_executor = new NestLoopJoinExecutor(context, join_output_schema, left_executor, right_executor, join_filters, ban_all);
    // sub query in join conditions
    left_executor = build_sub_query_executor(left_executor, selects->relations[0], selects->joins[i].conditions, selects->joins[i].condition_num);
  }
  return left_executor;
}

CompOp symmetric_op(CompOp op) {
  switch(op) {
  case EQUAL_TO:
    return EQUAL_TO;
  case LESS_EQUAL:
    return GREAT_EQUAL;
  case NOT_EQUAL:
    return NOT_EQUAL;
  case LESS_THAN:
    return GREAT_THAN;
  case GREAT_EQUAL:
    return LESS_EQUAL;
  case GREAT_THAN:
    return LESS_THAN;
  case IS:
    return IS;
  case IS_NOT:
    return IS_NOT;
  case IN_OP:
    return IN_OP;
  case NOT_IN_OP:
    return NOT_IN_OP;
  default:
    return NO_OP;
  }
}

void sub_selects_init(Selects* selects) {
  // 当子查询的查询条件中出现了多个table_name，那么将该子查询认为是多表查询
  std::unordered_set<std::string> table_name_set;
  for (int i = 0; i < selects->relation_num; ++i) {
    table_name_set.insert(selects->relations[i]);
  }
  for (int i = 0; i < selects->condition_num; ++i) {
    Condition condition = selects->conditions[i];
    if (condition.left_is_attr && condition.left_attr.relation_name != nullptr && table_name_set.count(condition.left_attr.relation_name) == 0) {
      selects->relations[selects->relation_num++] = condition.left_attr.relation_name;
      table_name_set.insert(condition.left_attr.relation_name);
    }
    if (condition.right_is_attr && condition.right_attr.relation_name != nullptr && table_name_set.count(condition.right_attr.relation_name) == 0) {
      selects->relations[selects->relation_num++] = condition.right_attr.relation_name;
      table_name_set.insert(condition.right_attr.relation_name);
    }
  }
}

Executor *ExecutorBuilder::build_sub_query_executor(Executor *executor, char *table_name, Condition conditions[], size_t condition_num) {
  Executor *right_executor;
  Executor *left_executor = executor;
  for (int i = 0; i < condition_num; i++) {
    Condition condition = conditions[i];
    if (condition.left_is_select && condition.right_is_select) {
      continue;
    }
    if (condition.left_is_select) {
      sub_selects_init(condition.left_selects);
      right_executor = build(condition.left_selects);
      if (condition.right_attr.relation_name == nullptr) {
        condition.right_attr.relation_name = table_name;
      }
      left_executor = new SubQueryExecutor(nullptr, left_executor, condition.right_attr, symmetric_op(condition.comp), right_executor);
    }
    if (condition.right_is_select) {
      sub_selects_init(condition.right_selects);
      right_executor = build(condition.right_selects);
      if (condition.left_attr.relation_name == nullptr) {
        condition.left_attr.relation_name = table_name;
      }
      left_executor = new SubQueryExecutor(nullptr, left_executor, condition.left_attr, condition.comp, right_executor);
    }
  }
  return left_executor;
}
