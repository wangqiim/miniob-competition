//
// Created by emrick on 2021/10/31.
//

#include "executor_builder.h"
#include "nest_loop_join_executor.h"

Executor* ExecutorBuilder::build() {
  return build(&sql_->sstr.selection);
}

Executor* ExecutorBuilder::build(Selects *selects) {
  Executor *select_executor = build_select_executor(selects);
  Executor *executor = build_join_executor(select_executor, selects);

  if (sql_->sstr.selection.aggre_num != 0) {
    // todo(yqs): 基于executor建立agg_executor另行处理
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
      const RelAttr &attr = selects->attributes[i];
      // 前置校验项，对于多表查询，必须指定relation_name
      assert(nullptr != attr.relation_name);
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
  Filter::from_condition_with_table(selects->conditions, selects->condition_num, table, filters0, ban_all0);
  Executor *left_executor = new ScanExecutor(context, table, output_schema0, std::move(filters0), ban_all0);
  Executor *right_executor;

  for (int i = selects->relation_num-2; i >= 0; --i) {
    table = DefaultHandler::get_default().find_table(db_->name(), selects->relations[i]);
    TupleSchema output_schema;
    TupleSchema::from_table(table, output_schema);
    std::vector<Filter*> filters;
    bool ban_all = false;
    Filter::from_condition_with_table(selects->conditions, selects->condition_num, table, filters, ban_all);
    right_executor = new ScanExecutor(context, table, output_schema, std::move(filters), ban_all);

    TupleSchema join_output_schema;
    join_output_schema.append(left_executor->output_schema());
    join_output_schema.append(right_executor->output_schema());
    std::vector<Filter*> join_filters;
    Filter::from_condition(selects->conditions, selects->condition_num, join_filters, ban_all);
    left_executor = new NestLoopJoinExecutor(context, join_output_schema, left_executor, right_executor, join_filters, ban_all);
  }
  for (int i = 0; i < selects->condition_num; i++) {
    Condition condition = selects->conditions[i];
    if (condition.is_sub_select) {
      right_executor = build(condition.selects);
      left_executor = new SubQueryExecutor(context, left_executor, condition.left_attr, condition.comp, right_executor);
    }
  }
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
    Filter::from_condition_with_table(selects->joins[i].conditions, selects->joins[i].condition_num, table, filters, ban_all);
    if (!ban_all) {
      Filter::from_condition_with_table(selects->conditions, selects->condition_num, table, filters, ban_all);
    }
    right_executor = new ScanExecutor(context, table, output_schema, std::move(filters), ban_all);

    TupleSchema join_output_schema;
    join_output_schema.append(left_executor->output_schema());
    join_output_schema.append(right_executor->output_schema());
    std::vector<Filter*> join_filters;
    Filter::from_condition(selects->joins[i].conditions, selects->joins[i].condition_num, join_filters, ban_all, true);
    if (i == 0 && !ban_all) { // 对于最后一个join，需要对join_condition和selects->condition中的条件一起进行过滤
      Filter::from_condition(selects->conditions, selects->condition_num, join_filters, ban_all, true);
    }
    left_executor = new NestLoopJoinExecutor(context, join_output_schema, left_executor, right_executor, join_filters, ban_all);

    for (int j = 0; j < selects->joins[i].condition_num; j++) {
      Condition condition = selects->joins[i].conditions[j];
      if (condition.is_sub_select) {
        right_executor = build(condition.selects);
        left_executor = new SubQueryExecutor(context, left_executor, condition.left_attr, condition.comp, right_executor);
      }
    }
  }
  return left_executor;
}
