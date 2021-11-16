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
// Created by Wangyunlai on 2021/5/7.
//

#ifndef __OBSERVER_STORAGE_COMMON_CONDITION_FILTER_H_
#define __OBSERVER_STORAGE_COMMON_CONDITION_FILTER_H_

#include <sql/executor/value.h>
#include <sql/executor/tuple.h>
#include <map>
#include <utility>
#include "rc.h"
#include "sql/parser/parse.h"

#include "storage/common/meta_util.h"
#include "db.h"

struct Record;
class Table;

struct ConDesc {
  bool   is_attr;     // 是否属性，false 表示是值
  int    attr_index;  // 如果是属性，标记是属性中的第几个元素
  int    attr_length; // 如果是属性，表示属性值长度
  int    attr_offset; // 如果是属性，表示在记录中的偏移量
  bool   is_null;     // 如果是值类型，则要判断是否为null
  void * value;       // 如果是值类型，这里记录值的数据
};

class ConditionFilter {
public:
  virtual ~ConditionFilter();

  /**
   * Filter one record
   * @param rec
   * @return true means match condition, false means failed to match.
   */
  virtual bool filter(const Record &rec) const = 0;
};

class DefaultConditionFilter : public ConditionFilter {
public:
  DefaultConditionFilter();
  virtual ~DefaultConditionFilter();

  RC init(Table *table, const ConDesc &left, const ConDesc &right, AttrType attr_type, CompOp comp_op);
  RC init(Table &table, const Condition &condition);

  virtual bool filter(const Record &rec) const;

public:
  const ConDesc &left() const {
    return left_;
  }

  const ConDesc &right() const {
    return right_;
  }

  CompOp comp_op() const {
    return comp_op_;
  }

private:
  Table *  table_;
  ConDesc  left_;
  ConDesc  right_;
  AttrType attr_type_ = UNDEFINED;
  CompOp   comp_op_ = NO_OP;
};

class CompositeConditionFilter : public ConditionFilter {
public:
  CompositeConditionFilter() = default;
  virtual ~CompositeConditionFilter();

  RC init(const ConditionFilter *filters[], int filter_num);
  RC init(Table &table, const Condition *conditions, int condition_num);
  virtual bool filter(const Record &rec) const;

public:
  int filter_num() const {
    return filter_num_;
  }
  const ConditionFilter &filter(int index) const {
    return *filters_[index];
  }

private:
  RC init(const ConditionFilter *filters[], int filter_num, bool own_memory);
private:
  const ConditionFilter **      filters_ = nullptr;
  int                           filter_num_ = 0;
  bool                          memory_owner_ = false; // filters_的内存是否由自己来控制
};


struct CartesianConDesc {
  int table_index;
  int value_index;
};

class CartesianFilter {
public:
  virtual ~CartesianFilter() = default;

  /**
   * Filter cross multi table
   * @param rec
   * @return true means match condition, false means failed to match.
   */
  virtual bool filter(const Tuple &tuple) const = 0;
};

class DefaultCartesianFilter : public CartesianFilter {
public:
  DefaultCartesianFilter() = default;
  virtual ~DefaultCartesianFilter() = default;
  // tuples中的每个Tuple对应一个table的Tuple，CartesianConDesc.table_index是tuples的下标
  // 每个Tuple中的vector<TupleValue>表示table中的一行数据，CartesianConDesc.value_index是vector<TupleValue>的下标
  virtual bool filter(const Tuple &tuple) const override;

  RC init(const CartesianConDesc &left, const CartesianConDesc &right, CompOp comp_op);

private:
  CartesianConDesc  left_;
  CartesianConDesc  right_;
  CompOp   comp_op_ = NO_OP;
};

class CompositeCartesianFilter : public CartesianFilter {
public:
  CompositeCartesianFilter() = default;
  virtual ~CompositeCartesianFilter();

  RC init(std::vector<DefaultCartesianFilter *> &&filters, bool own_memory=false);
  virtual bool filter(const Tuple &tuple) const override;

private:
  std::vector<DefaultCartesianFilter *> filters_;
  bool memory_owner_ = false; // filters_的内存是否由自己来控制
};


struct FilterDesc {
  bool is_attr;
  std::string table_name;
  std::string field_name;
  Value value;
  // 为了适配支持现有的基于Record的过滤新增attr_length和attr_offset
  int attr_length = -1;
  int attr_offset = -1;
};

class Filter: public ConditionFilter {
public:
  Filter(FilterDesc left, FilterDesc right, CompOp comp_op): left_(std::move(left)), right_(std::move(right)), comp_op_(comp_op) {}
  ~Filter() = default;

  bool filter(const Tuple &left_tuple, TupleSchema &left_schema, const Tuple &right_tuple, TupleSchema &right_schema) const;

  // 绑定单个Table，初始化left_和right_中的attr_length和attr_offset
  // left_和right_中的table_name必须是相同的，否则当前filter不能作为对单个Table的Record进行过滤
  RC bind_table(Table *table);

  // 为了适配支持现有的基于Record的过滤，再调用支持Record之前，当前Filter必须先调用bind_table
  // 此时当前的Filter只能够对单个Table中的字段进行过滤
  bool filter(const Record &rec) const;

  static void from_condition(Condition *conditions, size_t condition_num, Table *table, std::vector<Filter*> &filters, bool &ban_all, bool attr_only=false, Db *db=nullptr);

private:
  FilterDesc  left_;
  FilterDesc  right_;
  CompOp   comp_op_ = NO_OP;
};

bool compare_result(int cmp_result, CompOp comp_op);

#endif // __OBSERVER_STORAGE_COMMON_CONDITION_FILTER_H_