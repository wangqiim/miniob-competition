//
// Created by emrick on 2021/10/27.
//

#include "sub_query_executor.h"
#include <unordered_set>

SubQueryExecutor::SubQueryExecutor(ExecutorContext* context,
                                   Executor *left_executor, RelAttr left_attr,
                                   CompOp op,
                                   Executor *right_executor):
                                   Executor(context, left_executor->output_schema()),
                                   left_executor_(left_executor), left_attr_(left_attr),
                                   op_(op),
                                   right_executor_(right_executor) {}

RC SubQueryExecutor::init() {
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

struct ValueEqual {
  bool operator()(const std::shared_ptr<TupleValue> &lhs, const std::shared_ptr<TupleValue> &rhs) const
  {
    return lhs->compare(*rhs) == 0;
  }
};

struct ValueHash {
  size_t operator()(const std::shared_ptr<TupleValue> &v) const
  {
    if (v->Type() == CHARS || v->Type() == DATES) {
      return std::hash<std::string>()((const char*)v->value_pointer());
    } else if(v->Type() == INTS) {
      return std::hash<int>()(*(const int*)v->value_pointer());
    } else if (v->Type() == FLOATS) {
      return std::hash<float>()(*(const float*)v->value_pointer());
    } else {
      return 0;
    }
  }
};

RC SubQueryExecutor::next(TupleSet &tuple_set, std::vector<Filter*> *filters) {
  // pre check
  if (op_ != IN_OP && op_ != NOT_IN_OP) {
    if (right_executor_->output_schema().fields().size() != 0) {
      return RC::INTERNAL;
    }
    if (right_executor_->output_schema().Get_agg_descs().size() == 0) {
      return RC::INTERNAL;
    }
  } else { // in or not in
    if (right_executor_->output_schema().fields().size() > 0 && right_executor_->output_schema().fields().size() != 1) {
      return RC::INTERNAL;
    }
  }

  tuple_set.set_schema(output_schema_);
  TupleSet left_tuple_set;
  RC rc = left_executor_->next(left_tuple_set);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  TupleSet right_tuple_set;
  rc = right_executor_->next(right_tuple_set);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  if (op_ != IN_OP && op_ != NOT_IN_OP && right_tuple_set.size() == 0) {
    return RC::INTERNAL;
  }

  if (left_tuple_set.size() == 0) {
    return RC::SUCCESS;
  }

  int right_field_index = 0;

  std::map<std::string, std::map<std::string, int>> left_table_field_index = left_tuple_set.get_schema().table_field_index();
  auto find_left_table = left_table_field_index.find(left_attr_.relation_name);
  if (find_left_table == left_table_field_index.end()) {
    return RC::INVALID_ARGUMENT;
  }
  auto find_left_field = find_left_table->second.find(left_attr_.attribute_name);
  if (find_left_field == find_left_table->second.end()) {
    return RC::INVALID_ARGUMENT;
  }
  int left_field_index = find_left_field->second;
  
  std::unordered_set<std::shared_ptr<TupleValue>, ValueHash, ValueEqual> tuple_value_set;
  for (const auto & right_tuple : right_tuple_set.tuples()) {
    tuple_value_set.insert(right_tuple.get_pointer(right_field_index));
  }

  std::vector<int> left_tuple_index = output_schema_.index_in(left_tuple_set.get_schema());
  std::shared_ptr<TupleValue> left_value;
  for (auto & left_tuple : left_tuple_set.tuples()) {
    left_value = left_tuple.get_pointer(left_field_index);
    bool valid;
    if (op_ == IN_OP || op_ == NOT_IN_OP) { // in (select xxx) or not in (select xxx)
      int count = tuple_value_set.count(left_value);
      valid = ((op_ == IN_OP && count != 0) || (op_ == NOT_IN_OP && count == 0));
    } else { // [=,<,>,...] (select xxx)
      valid = compare_result(left_value->compare(**tuple_value_set.begin()), op_);
    }
    if (valid) {
      Tuple result_tuple;
      result_tuple.add(left_tuple, left_tuple_index);
      tuple_set.add(std::move(result_tuple));
    }
  }
  return RC::SUCCESS;
}