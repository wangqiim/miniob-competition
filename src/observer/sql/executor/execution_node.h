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
// Created by Wangyunlai on 2021/5/13.
//

#ifndef __OBSERVER_SQL_EXECUTOR_EXECUTION_NODE_H_
#define __OBSERVER_SQL_EXECUTOR_EXECUTION_NODE_H_

#include <vector>
#include <map>
#include "storage/common/condition_filter.h"
#include "sql/executor/tuple.h"

class Table;
class Trx;

class ExecutionNode {
public:
  ExecutionNode() = default;
  virtual ~ExecutionNode() = default;

  virtual RC execute(TupleSet &tuple_set) = 0;
};

class SelectExeNode : public ExecutionNode {
public:
  SelectExeNode();
  virtual ~SelectExeNode();

  RC init(Trx *trx, Table *table, TupleSchema && tuple_schema, std::vector<DefaultConditionFilter *> &&condition_filters);

  RC execute(TupleSet &tuple_set) override;
private:
  Trx *trx_ = nullptr;
  Table  * table_;
  TupleSchema  tuple_schema_;
  std::vector<DefaultConditionFilter *> condition_filters_;
};

class cartesianExeNode : public ExecutionNode {
public:
  cartesianExeNode() = default;
  ~cartesianExeNode() {
    delete condition_filter_;
  }

  RC init(Trx *trx, std::vector<TupleSet> &&tuple_sets,
          TupleSchema &&tuple_schema,
          CompositeCartesianFilter *condition_filter,
          std::map<std::string, std::pair<int, std::map<std::string, int>>> &&table_value_index);

  RC execute(TupleSet &tuple_set) override;

private:
  Trx *trx_ = nullptr;
  std::vector<TupleSet> tuple_sets_;
  CompositeCartesianFilter *condition_filter_;
  TupleSchema  tuple_schema_;
  // {table_name: (table_index, {value_name: value_index})}
  std::map<std::string, std::pair<int, std::map<std::string, int>>> table_value_index_;
};

// 拥有DefaultConditionFilter和AggreDesc的所有按，析构时需要释放内存
class AggregateExeNode {
public:
  AggregateExeNode() = default;
  ~AggregateExeNode();
  RC init(Trx *trx, Table *table, std::vector<AggreDesc *> &&aggre_descs, std::vector<DefaultConditionFilter *> &&condition_filters);

  /* tuple_set is not used here! */
  RC execute(AggreSet &aggre_set);
private:
  Trx *trx_ = nullptr;
  Table * table_;
  
  std::vector<AggreDesc *> aggres_;

  std::vector<DefaultConditionFilter *> condition_filters_;
};


#endif //__OBSERVER_SQL_EXECUTOR_EXECUTION_NODE_H_
