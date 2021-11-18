//
// Created by emrick on 2021/10/27.
//

#include "sub_query_executor.h"
#include <unordered_set>

SubQueryExecutor::SubQueryExecutor(ExecutorContext* context,
                                   Executor *left_executor, RelAttr left_attr,
                                   CompOp op,
                                   Executor *right_executor,
                                   std::vector<Condition> &&multi_table_conditions):
                                   Executor(context, left_executor->output_schema()),
                                   left_executor_(left_executor), left_attr_(left_attr),
                                   op_(op),
                                   right_executor_(right_executor),
                                   multi_table_conditions_(std::move(multi_table_conditions)){}

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


RC SubQueryExecutor::add_multi_table_filter(const TupleField &field, TupleValue &value, std::vector<Filter*> *filters) {
  const std::map<std::string, std::map<std::string, int>> field_index = left_executor_->output_schema().table_field_index();
  Filter* filter;
  for (auto multi_condition : multi_table_conditions_) {
    Condition condition = multi_condition;
    bool valid_condition = false;
    // left_attr op right_attr => left_value op right_attr
    if (condition.left_is_attr && condition.left_attr.relation_name != nullptr 
        && field_index.count(condition.left_attr.relation_name) != 0
        && condition.right_is_attr && condition.right_attr.relation_name != nullptr
        && field_index.count(condition.right_attr.relation_name) == 0) {
      condition.left_is_attr = 0;
      condition.left_value.data = value.value_pointer();
      condition.left_value.type = value.Type();
      valid_condition = true;
    }
    // left_attr op right_attr => left_attr op right_value
    if (condition.right_is_attr && condition.right_attr.relation_name != nullptr 
    && field_index.count(condition.right_attr.relation_name) != 0
    && condition.left_is_attr && condition.left_attr.relation_name != nullptr
    && field_index.count(condition.left_attr.relation_name) == 0) {
      condition.right_is_attr = 0;
      condition.right_value.data = value.value_pointer();
      condition.right_value.type = value.Type();
      valid_condition = true;
    }
    if (valid_condition) {
      bool ban_all = false;
      filter = Filter::from_condition(condition, ban_all);
      if (ban_all) {
        filters->clear();
        return RC::SUCCESS;
      }
      filters->push_back(filter);
    }
  }
  return RC::SUCCESS;
}

RC SubQueryExecutor::remove_multi_table_filter(std::vector<Filter*> *filters, size_t num) {
  for (int i = 0; i < num; ++i) {
    if (filters->empty()) {
      return RC::SUCCESS;
    } else {
      filters->pop_back();
    }
  }
  return RC::SUCCESS;
}

RC SubQueryExecutor::next(TupleSet &tuple_set, std::vector<Filter*> *filters) {
  // pre check
  if (op_ != IN_OP && op_ != NOT_IN_OP) {
    if (!right_executor_->output_schema().fields().empty()) {
      return RC::INTERNAL;
    }
    if (right_executor_->output_schema().Get_agg_descs().empty()) {
      return RC::INTERNAL;
    }
  } else { // in or not in
    if (!right_executor_->output_schema().fields().empty() && right_executor_->output_schema().fields().size() != 1) {
      return RC::INTERNAL;
    }
  }

  tuple_set.set_schema(output_schema_);
  TupleSet left_tuple_set;
  RC rc = left_executor_->next(left_tuple_set, filters);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  if (left_tuple_set.size() == 0) {
    return RC::SUCCESS;
  }

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
  int right_field_index = 0;
  TupleSet tmp_tuple_set;

  std::vector<int> left_tuple_index = output_schema_.index_in(left_tuple_set.get_schema());

  if (multi_table_conditions_.empty()) {
    TupleSet right_tuple_set;
    rc = right_executor_->next(right_tuple_set);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    if (op_ != IN_OP && op_ != NOT_IN_OP && right_tuple_set.size() == 0) {
      return RC::SUCCESS;
    }
    std::unordered_set<std::shared_ptr<TupleValue>, ValueHash, ValueEqual> tuple_value_set;
    for (const auto & right_tuple : right_tuple_set.tuples()) {
      tuple_value_set.insert(right_tuple.get_pointer(right_field_index));
    }
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
        tmp_tuple_set.add(std::move(left_tuple));
      }
    }
  } else {
    TupleSet right_tuple_set;
    std::shared_ptr<TupleValue> left_value;
    std::unordered_set<std::shared_ptr<TupleValue>, ValueHash, ValueEqual> tuple_value_set;
    std::vector<Filter*> multi_table_filters;
    auto * right_next_filters = new std::vector<Filter*>;
    if (filters) {
      for (auto & filter : *filters) {
        right_next_filters->push_back(filter);
      }
    }
    for (auto & left_tuple : left_tuple_set.tuples()) {
      left_value = left_tuple.get_pointer(left_field_index);
      multi_table_filters.clear();
      add_multi_table_filter(left_tuple_set.get_schema().field(left_field_index), *left_value, &multi_table_filters);
      for(auto & filter: multi_table_filters) {
        right_next_filters->push_back(filter);
      }
      right_tuple_set.clear();
      rc = right_executor_->next(right_tuple_set, right_next_filters);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      if (op_ != IN_OP && op_ != NOT_IN_OP && right_tuple_set.size() == 0) {
        continue;
      }
      tuple_value_set.clear();
      for (const auto & right_tuple : right_tuple_set.tuples()) {
        tuple_value_set.insert(right_tuple.get_pointer(right_field_index));
      }
      bool valid;
      if (op_ == IN_OP || op_ == NOT_IN_OP) { // in (select xxx) or not in (select xxx)
        int count = tuple_value_set.count(left_value);
        valid = ((op_ == IN_OP && count != 0) || (op_ == NOT_IN_OP && count == 0));
      } else { // [=,<,>,...] (select xxx)
        valid = compare_result(left_value->compare(**tuple_value_set.begin()), op_);
      }
      if (valid) {
        tmp_tuple_set.add(std::move(left_tuple));
      }

      remove_multi_table_filter(right_next_filters, multi_table_filters.size());
    }
  }

  // check by filters
  for (const auto & tuple : tmp_tuple_set.tuples()) {
    bool valid = true;
    if (filters != nullptr) {
      for (const auto &filter : *filters) {
        if(!filter->filter(tuple, left_tuple_set.get_schema())) {
          valid = false;
          break;
        }
      }
    }
    if (valid) {
      Tuple result_tuple;
      result_tuple.add(tuple, left_tuple_index);
      tuple_set.add(std::move(result_tuple));
    }
  }
  return RC::SUCCESS;
}