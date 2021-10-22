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
// Created by Wangyunlai on 2021/5/14.
//

#include "sql/executor/execution_node.h"
#include "storage/common/table.h"
#include "common/log/log.h"

SelectExeNode::SelectExeNode() : table_(nullptr) {
}

SelectExeNode::~SelectExeNode() {
  for (DefaultConditionFilter * &filter : condition_filters_) {
    delete filter;
  }
  condition_filters_.clear();
}

RC
SelectExeNode::init(Trx *trx, Table *table, TupleSchema &&tuple_schema, std::vector<DefaultConditionFilter *> &&condition_filters) {
  trx_ = trx;
  table_ = table;
  tuple_schema_ = tuple_schema;
  condition_filters_ = std::move(condition_filters);
  return RC::SUCCESS;
}

void record_reader(const char *data, void *context) {
  TupleRecordConverter *converter = (TupleRecordConverter *)context;
  converter->add_record(data);
}
RC SelectExeNode::execute(TupleSet &tuple_set) {
  CompositeConditionFilter condition_filter;
  condition_filter.init((const ConditionFilter **)condition_filters_.data(), condition_filters_.size());

  tuple_set.clear();
  tuple_set.set_schema(tuple_schema_);
  TupleRecordConverter converter(table_, tuple_set);
  return table_->scan_record(trx_, &condition_filter, -1, (void *)&converter, record_reader);
}

RC JoinExeNode::init(Trx *trx, std::vector<TupleSet> &&tuple_sets,
                     TupleSchema &&tuple_schema,
                     CompositeJoinFilter *condition_filter,
                     std::map<std::string, std::pair<int, std::map<std::string, int>>> &&table_value_index) {
  trx_ = trx;
  tuple_sets_ = std::move(tuple_sets);
  condition_filter_ = condition_filter;
  tuple_schema_ = tuple_schema;
  table_value_index_ = std::move(table_value_index);
  return RC::SUCCESS;
}

RC JoinExeNode::execute(TupleSet &tuple_set) {
  tuple_set.set_schema(tuple_schema_);
  for (auto iter = TupleSetDescartesIterator(&tuple_sets_); !iter.End(); ++iter) {
    std::unique_ptr<std::vector<Tuple>> tuples = *iter;
    if (condition_filter_->filter(tuples.get())) {
      Tuple validate_tuple;
      for(const auto & field :tuple_schema_.fields()) {
        auto find_table_index = table_value_index_.find(field.table_name());
        assert(find_table_index != table_value_index_.end());
        int table_index = find_table_index->second.first;
        std::map<std::string, int> &value_index_map = find_table_index->second.second;
        auto find_value_index = value_index_map.find(field.field_name());
        assert(find_value_index != value_index_map.end());
        int value_index = find_value_index->second;
        validate_tuple.add(tuples->at(table_index).get_pointer(value_index));
      }
      tuple_set.add(std::move(validate_tuple));
    }
  }
  return RC::SUCCESS;
}