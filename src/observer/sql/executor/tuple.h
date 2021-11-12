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

#ifndef __OBSERVER_SQL_EXECUTOR_TUPLE_H_
#define __OBSERVER_SQL_EXECUTOR_TUPLE_H_

#include <memory>
#include <vector>
#include <map>

#include "sql/parser/parse.h"
#include "sql/executor/value.h"

class Table;
class TupleSchema;

class Tuple {
public:
  Tuple() = default;

  Tuple(const Tuple &other);

  ~Tuple();

  Tuple(Tuple &&other) noexcept ;
  Tuple & operator=(Tuple &&other) noexcept ;

  void add(TupleValue *value);
  void add(const std::shared_ptr<TupleValue> &other);
  void add(int value);
  void add(float value);
  void add(const char *s, int len);
  void add(const Tuple &tuple, const std::vector<int> &field_index);
  // add null
  void add_null();

  const std::vector<std::shared_ptr<TupleValue>> &values() const {
    return values_;
  }

  int size() const {
    return values_.size();
  }

  const TupleValue &get(int index) const {
    return *values_[index];
  }

  const std::shared_ptr<TupleValue> &get_pointer(int index) const {
    return values_[index];
  }

private:
  std::vector<std::shared_ptr<TupleValue>>  values_;
};

class TupleField {
public:
  TupleField(AttrType type, const char *table_name, const char *field_name, int order) :
          type_(type), table_name_(table_name), field_name_(field_name), order_(order) {
  }

  AttrType  type() const{
    return type_;
  }

  const char *table_name() const {
    return table_name_.c_str();
  }
  const char *field_name() const {
    return field_name_.c_str();
  }
  bool order() const { return order_; }
  std::string to_string() const;
private:
  AttrType  type_;
  std::string table_name_;
  std::string field_name_;
  int order_;
};

class TupleSchema {
public:
  TupleSchema() = default;
  ~TupleSchema() = default;

  void add(AttrType type, const char *table_name, const char *field_name, int order=0);
  void add_if_not_exists(AttrType type, const char *table_name, const char *field_name, int order=0);
  // void merge(const TupleSchema &other);
  void append(const TupleSchema &other);

  const std::vector<TupleField> &fields() const { return fields_; }
  std::vector<int> index_in(TupleSchema &schema);

  bool empty() const { return fields_.size() == 0; }

  const TupleField &field(int index) const { return fields_[index]; }
  const std::map<std::string, std::map<std::string, int>> &table_field_index() {
    if (!table_field_index_.empty()) {
      return table_field_index_;
    }
    const char *table_name;
    const char *field_name;
    for (int index = 0; index < fields_.size(); index++) {
      TupleField &field = fields_[index];
      table_name = field.table_name();
      field_name = field.field_name();
      auto find_table = table_field_index_.find(table_name);
      if (find_table == table_field_index_.end()) {
        std::map<std::string, int> field_index{{field_name, index}};
        table_field_index_.emplace(table_name, field_index);
      } else {
        find_table->second[field_name] = index;
      }
    }
    return table_field_index_;
  }

  int index_of_field(const char *table_name, const char *field_name) const;

  void clear() { fields_.clear(); }

  void print(std::ostream &os, bool multi_table = false, bool endl = true) const;

  static void from_table(const Table *table, TupleSchema &schema);
  static void from_table(const std::vector<Table*> &tables, TupleSchema &schema);
  static void schema_add_field(Table *table, const char *field_name, TupleSchema &schema);

private:
  std::vector<TupleField> fields_;
  std::map<std::string, std::map<std::string, int>> table_field_index_;
};

class TupleSet {
public:
  TupleSet() = default;
  TupleSet(TupleSet &&other);
  explicit TupleSet(const TupleSchema &schema) : schema_(schema) {
  }
  TupleSet &operator =(TupleSet &&other);

  ~TupleSet() = default;

  void set_schema(const TupleSchema &schema);

  TupleSchema &get_schema();

  void add(Tuple && tuple);

  void clear();

  bool is_empty() const;
  int size() const;
  const Tuple &get(int index) const;
  const std::vector<Tuple> &tuples() const;

  void print(std::ostream &os, bool multi_table = false) const;
public:
  const TupleSchema &schema() const {
    return schema_;
  }
private:
  std::vector<Tuple> tuples_;
  TupleSchema schema_;

};

class TupleSetDescartesIterator {
public:
  explicit TupleSetDescartesIterator(std::vector<TupleSet> *tuple_sets): tuple_sets_(tuple_sets) {
    for (const auto & tuple_set : *tuple_sets) {
      if (tuple_set.size() == 0) {
        end = true;
      }
      sizes_.push_back(tuple_set.size());
      indexes_.push_back(0);
    }
  }

  ~TupleSetDescartesIterator() {
    std::vector<int> tmp;
    sizes_.swap(tmp);
    std::vector<int> tmp2;
    sizes_.swap(tmp2);
    // 迭代器并不拥有tuple_sets_
  }

  std::unique_ptr<std::vector<Tuple>> operator *() {
    auto tuple_result = std::make_unique<std::vector<Tuple>>();
    int value_index;
    for (int table_index = 0; table_index < indexes_.size(); ++table_index) {
      value_index = indexes_[table_index];
      if (value_index < sizes_[table_index]) {
        TupleSet &tuple_set = (*tuple_sets_)[table_index];
        tuple_result->push_back(tuple_set.get(value_index));
      }
    }
    return tuple_result;
  }

  void operator ++() {
    int i = indexes_.size() - 1;
    while(i >= 0) {
      if (indexes_[i] < sizes_[i] - 1) {
        indexes_[i]++;
        return;
      } else {
        indexes_[i] = 0;
        i--;
      }
    }
    end = true;
  }

  bool End() {
    return end;
  }

private:
  std::vector<int> sizes_;
  std::vector<int> indexes_;
  std::vector<TupleSet> *tuple_sets_;
  bool end = false;
};

class TupleRecordConverter {
public:
  TupleRecordConverter(Table *table, TupleSet &tuple_set);

  void add_record(const char *record);

private:
  Table *table_;
  TupleSet &tuple_set_;
};

struct AggreDesc {
  AggreType aggre_type;
  int       is_attr;          // 是否属性，false 表示是值
  char *    relation_name;    // 如果是属性，则记录表名(用来决定最输出是tb.attr或attr)
  char *    attr_name;        // 如果是属性，则记录属性名
  int       is_star;          // *时，is_attr = 0, 用于辅助print时的表头和输入一致
  float     value;            // 如果是值类型，这里记录值的数据
};

// aggregate result set
class AggreSet {
public:
  AggreSet() = default;
  // 释放内存
  ~AggreSet() {
    for (int i = 0; i < aggres_->size(); i++) {
      if (aggre_max_[i] != nullptr) {
        delete aggre_max_[i];
      }
      if (aggre_min_[i] != nullptr) {
        delete aggre_min_[i];
      }
    }
  };

  void init(std::vector<AggreDesc *> &aggres);
  
  // 根据每一个记录更新所有聚合函数的中间属性: sum, count等
  void update_aggre_set(int aggre_index, bool is_null, AttrType attr_type, int len, const char *value);
  
  // 生成最后的输出tuple
  RC finish_aggregate();
  
  void print(std::ostream &os) const;


private:
  void aggre_type_print(std::ostream &os, AggreType type) const; 
  void aggre_attr_print(std::ostream &os, int aggre_index) const;

  std::vector<AggreDesc *> *aggres_;
  std::vector<AttrType> aggre_attr_type_;

  std::vector<char *> aggre_max_;
  std::vector<char *> aggre_min_;
  std::vector<float> aggre_avg_;
  std::vector<float> aggre_sum_;
  std::vector<float> aggre_count_;

  Tuple tuple_;
};

// table_scan callback工具类
class TupleAggregateUtil {
public:
  TupleAggregateUtil(Table * table, std::vector<AggreDesc *> &aggres, AggreSet &aggre_set) :
    table_(table), aggres_(aggres), aggre_set_(aggre_set) {
      aggre_set_.init(aggres_);
    }

  void aggregate(const char *record);
private:
  Table * table_;
  std::vector<AggreDesc *> &aggres_;
  AggreSet &aggre_set_;
};

#endif //__OBSERVER_SQL_EXECUTOR_TUPLE_H_
