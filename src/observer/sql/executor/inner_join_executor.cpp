//
// Created by emrick on 2021/10/27.
//

#include "inner_join_executor.h"

InnerJoinExecutor::InnerJoinExecutor(ExecutorContext* context,
                                     const TupleSchema &output_schema,
                                     Executor *left_executor,
                                     Executor *right_executor,
                                     std::vector<Filter*> condition_filters):
                                     Executor(context, output_schema), output_schema_(output_schema),
                                     left_executor_(left_executor), right_executor_(right_executor),
                                     condition_filters_(std::move(condition_filters)) {}

RC InnerJoinExecutor::init() {
  RC rc = left_executor_->init();
  if (rc != RC::SUCCESS) {
    return rc;
  }
  rc = right_executor_->init();
  if (rc != RC::SUCCESS) {
    return rc;
  }
  return RC::SUCCESS;
}



RC InnerJoinExecutor::next(TupleSet &tuple_set, std::vector<Filter*> *filters) {
  TupleSet left_tuple_set;
  left_executor_->next(left_tuple_set);
//  for (const auto & tuple : left_tuple_set.tuples()) {
//
//  }
  return RC::SUCCESS;
}