//
// Created by emrick on 2021/10/27.
//

#include "nest_loop_join_executor.h"
#include <vector>

NestLoopJoinExecutor::NestLoopJoinExecutor(ExecutorContext* context, const TupleSchema &output_schema,
                                     Executor *left_executor,
                                     Executor *right_executor,
                                     std::vector<Filter*> condition_filters,
                                     bool ban_all):
                                     Executor(context, output_schema),
                                     left_executor_(left_executor), right_executor_(right_executor),
                                     condition_filters_(), ban_all_(ban_all) {
  // 在select * from t1, t2, t3 where t2.id = t3.id; 
  // 上述语句中，t2.id 这个条件同时塞到了(t1, t2) 和((t1, t2), t3)两个excutor中，因此这里需要过滤
  for (Filter * filter : condition_filters) {
    // 如果条件是属性，必须在该节点关联的表中
    if (filter->left().is_attr && ((TupleSchema &)output_schema).table_field_index().count(filter->left().table_name) == 0) {
      continue;
    }
    if (filter->right().is_attr && ((TupleSchema &)output_schema).table_field_index().count(filter->right().table_name) == 0) {
      continue;
    }
    condition_filters_.push_back(filter);
  }
};

RC NestLoopJoinExecutor::init() {
  RC rc;
  rc = left_executor_->init();
  if(rc != RC::SUCCESS) {
    return rc;
  }
  rc = right_executor_->init();
  if(rc != RC::SUCCESS) {
    return rc;
  }
  return RC::SUCCESS;
}

RC NestLoopJoinExecutor::next(TupleSet &tuple_set, std::vector<Filter*> *filters) {
  tuple_set.set_schema(output_schema_);
  if (ban_all_) {
    return RC::SUCCESS;
  }
  TupleSet left_tuple_set;
  left_executor_->next(left_tuple_set);
  TupleSet right_tuple_set;
  right_executor_->next(right_tuple_set);

  if (left_tuple_set.size() == 0 || right_tuple_set.size() == 0) {
    return RC::SUCCESS;
  }
  
  std::vector<int> left_tuple_index = output_schema_.index_in(left_tuple_set.get_schema());
  std::vector<int> right_tuple_index = output_schema_.index_in(right_tuple_set.get_schema());

  for (const auto & left_tuple : left_tuple_set.tuples()) {
    for (auto & right_tuple: right_tuple_set.tuples()) {
      bool valid = true;
      if (filters != nullptr) {
        for (auto & tmp_filter : *filters) {
          if (!tmp_filter->filter(left_tuple, left_tuple_set.get_schema(), right_tuple, right_tuple_set.get_schema())) {
            valid = false;
            break;
          }
        }
      }
      if (!valid) { continue; }
      for (auto & self_filter : condition_filters_) {
        if (!self_filter->filter(left_tuple, left_tuple_set.get_schema(), right_tuple, right_tuple_set.get_schema())) {
          valid = false;
          break;
        }
      }
      if (valid) {
        Tuple result_tuple;
        result_tuple.add(left_tuple, left_tuple_index);
        result_tuple.add(right_tuple, right_tuple_index);
        tuple_set.add(std::move(result_tuple));
      }
    }
  }
  return RC::SUCCESS;
}