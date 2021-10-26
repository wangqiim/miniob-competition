//
// Created by emrick on 2021/10/27.
//

#include "sub_query_executor.h"
#include <set>
#include <vector>

SubQueryExecutor::SubQueryExecutor(ExecutorContext* context, const TupleSchema &output_schema,
                                   Executor *current_executor,
                                   Executor *sub_executor,
                                   std::vector<Filter*> condition_filters):
                                   Executor(context, output_schema),
                                   current_executor_(current_executor), sub_executor_(sub_executor),
                                   condition_filters_(std::move(condition_filters)) {};

RC SubQueryExecutor::init() {
  assert(condition_filters_.size() == 1);
  current_executor_->init();
  sub_executor_->init();
  return RC::SUCCESS;
}

RC SubQueryExecutor::next(TupleSet &tuple_set, std::vector<Filter*> *filters) {
  TupleSet sub_tuple_set;
  sub_executor_->next(sub_tuple_set);
  assert(sub_tuple_set.get_schema().fields().size() == 1);
  TupleSet current_tuple_set;
  current_executor_->next(current_tuple_set);
//  Filter *filter = condition_filters_[0];


  return RC::SUCCESS;
}