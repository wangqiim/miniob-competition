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

#include <algorithm>

#include "sql/executor/tuple.h"
#include "storage/common/table.h"
#include "common/log/log.h"
#include "common/lang/bitmap.h"
#include "storage/common/record_manager.h"

Tuple::Tuple(const Tuple &other) = default;

Tuple::Tuple(Tuple &&other) noexcept : values_(std::move(other.values_)) {
}

Tuple & Tuple::operator=(Tuple &&other) noexcept {
  if (&other == this) {
    return *this;
  }

  values_.clear();
  values_.swap(other.values_);
  return *this;
}

Tuple::~Tuple() {
}

// add (Value && value)
void Tuple::add(TupleValue *value) {
  values_.emplace_back(value);
}
void Tuple::add(const std::shared_ptr<TupleValue> &other) {
  values_.emplace_back(other);
}
void Tuple::add(int value) {
  add(new IntValue(value));
}

void Tuple::add(float value) {
  add(new FloatValue(value));
}

void Tuple::add(const char *s, int len) {
  add(new StringValue(s, len));
}
void Tuple::add_null() {
  add(new NullValue());
}

////////////////////////////////////////////////////////////////////////////////

std::string TupleField::to_string() const {
  return std::string(table_name_) + "." + field_name_ + std::to_string(type_);
}

////////////////////////////////////////////////////////////////////////////////
void TupleSchema::from_table(const Table *table, TupleSchema &schema) {
  const char *table_name = table->name();
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = 0; i < field_num; i++) {
    const FieldMeta *field_meta = table_meta.field(i);
    if (field_meta->visible()) {
      schema.add(field_meta->type(), table_name, field_meta->name());
    }
  }
}

void TupleSchema::add(AttrType type, const char *table_name, const char *field_name) {
  fields_.emplace_back(type, table_name, field_name);
}

void TupleSchema::add_if_not_exists(AttrType type, const char *table_name, const char *field_name) {
  for (const auto &field: fields_) {
    if (0 == strcmp(field.table_name(), table_name) &&
        0 == strcmp(field.field_name(), field_name)) {
      return;
    }
  }

  add(type, table_name, field_name);
}

void TupleSchema::append(const TupleSchema &other) {
  fields_.reserve(fields_.size() + other.fields_.size());
  for (const auto &field: other.fields_) {
    fields_.emplace_back(field);
  }
}

int TupleSchema::index_of_field(const char *table_name, const char *field_name) const {
  const int size = fields_.size();
  for (int i = 0; i < size; i++) {
    const TupleField &field = fields_[i];
    if (0 == strcmp(field.table_name(), table_name) && 0 == strcmp(field.field_name(), field_name)) {
      return i;
    }
  }
  return -1;
}

void TupleSchema::print(std::ostream &os, bool multi_table) const {
  if (fields_.empty()) {
    os << "No schema";
    return;
  }

  for (std::vector<TupleField>::const_iterator iter = fields_.begin(), end = --fields_.end();
       iter != end; ++iter) {
    if (multi_table) {
      os << iter->table_name() << ".";
    }
    os << iter->field_name() << " | ";
  }

  if (multi_table) {
    os << fields_.back().table_name() << ".";
  }
  os << fields_.back().field_name() << std::endl;
}

/////////////////////////////////////////////////////////////////////////////
TupleSet::TupleSet(TupleSet &&other) : tuples_(std::move(other.tuples_)), schema_(other.schema_){
  other.schema_.clear();
}

TupleSet &TupleSet::operator=(TupleSet &&other) {
  if (this == &other) {
    return *this;
  }

  schema_.clear();
  schema_.append(other.schema_);
  other.schema_.clear();

  tuples_.clear();
  tuples_.swap(other.tuples_);
  return *this;
}

void TupleSet::add(Tuple &&tuple) {
  tuples_.emplace_back(std::move(tuple));
}

void TupleSet::clear() {
  tuples_.clear();
  schema_.clear();
}

void TupleSet::print(std::ostream &os, bool multi_table) const {
  if (schema_.fields().empty()) {
    LOG_WARN("Got empty schema");
    return;
  }

  schema_.print(os, multi_table);

  for (const Tuple &item : tuples_) {
    const std::vector<std::shared_ptr<TupleValue>> &values = item.values();
    for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values.begin(), end = --values.end();
          iter != end; ++iter) {
      (*iter)->to_string(os);
      os << " | ";
    }
    values.back()->to_string(os);
    os << std::endl;
  }
}

void TupleSet::set_schema(const TupleSchema &schema) {
  schema_ = schema;
}

const TupleSchema &TupleSet::get_schema() const {
  return schema_;
}

bool TupleSet::is_empty() const {
  return tuples_.empty();
}

int TupleSet::size() const {
  return tuples_.size();
}

const Tuple &TupleSet::get(int index) const {
  return tuples_[index];
}

const std::vector<Tuple> &TupleSet::tuples() const {
  return tuples_;
}

/////////////////////////////////////////////////////////////////////////////
TupleRecordConverter::TupleRecordConverter(Table *table, TupleSet &tuple_set) :
      table_(table), tuple_set_(tuple_set){
}

void TupleRecordConverter::add_record(const char *record) {
  const TupleSchema &schema = tuple_set_.schema();
  Tuple tuple;
  const TableMeta &table_meta = table_->table_meta();
  common::Bitmap null_bitmap((char *)record, align8(table_meta.field_num()));
  for (const TupleField &field : schema.fields()) {
    const FieldMeta *field_meta = table_meta.field(field.field_name());
    assert(field_meta != nullptr);
    int index = table_meta.field_index(field.field_name());
    if (null_bitmap.get_bit(index)) {
      tuple.add_null();
      continue;
    }
    switch (field_meta->type()) {
      case INTS: {
        int value = *(int*)(record + field_meta->offset());
        tuple.add(value);
      }
      break;
      case FLOATS: {
        float value = *(float *)(record + field_meta->offset());
        tuple.add(value);
      }
        break;
      case CHARS: {
        const char *s = record + field_meta->offset();  // 现在当做Cstring来处理
        tuple.add(s, strlen(s));
      }
      break;
      case DATES: {
        const char *s = record + field_meta->offset();  // 现在当做Cstring来处理
        tuple.add(s, strlen(s));
      }
      break;
      default: {
        LOG_PANIC("Unsupported field type. type=%d", field_meta->type());
      }
    }
  }

  tuple_set_.add(std::move(tuple));
}

void AggreSet::init(std::vector<AggreDesc *> &aggres) {
  aggres_ = &aggres;
  aggre_attr_type_.resize(aggres_->size(), AttrType::UNDEFINED);
  aggre_min_.resize(aggres_->size(), nullptr);
  aggre_max_.resize(aggres_->size(), nullptr);
  aggre_avg_.resize(aggres_->size(), 0);
  aggre_sum_.resize(aggres_->size(), 0);
  aggre_count_.resize(aggres_->size(), 0);
}

void AggreSet::update_aggre_set(int aggre_index, bool is_null, AttrType attr_type, int len, const char *value) {
  if (is_null) {
    aggre_count_[aggre_index]++;
    return;
  }
  assert(aggre_attr_type_[aggre_index] == AttrType::UNDEFINED || aggre_attr_type_[aggre_index] == attr_type);
  aggre_attr_type_[aggre_index] = attr_type;

  if (aggre_max_[aggre_index] == nullptr) {
    char *v_max = (char *)malloc(len);
    char *v_min = (char *)malloc(len);
    memcpy(v_max, value, len);
    memcpy(v_min, value, len);
    aggre_max_[aggre_index] = v_max;
    aggre_min_[aggre_index] = v_min;
  }

  if (attr_type == AttrType::INTS || attr_type == AttrType::FLOATS) {
    float t = 0;
    if (attr_type == AttrType::INTS) {
      t = *((int *)value);
    } else {
      t = *((float *)value);
    }
  }
  switch (attr_type) {
    case AttrType::INTS: {
      int t = *((int *)value);
      if (t > *(int *)aggre_max_[aggre_index]) {
        *(int *)aggre_max_[aggre_index] = t;
      }
      if (t < *(int *)aggre_min_[aggre_index]) {
        *(int *)aggre_min_[aggre_index] = t;
      }
      aggre_count_[aggre_index]++;
      aggre_sum_[aggre_index] += t;
      aggre_avg_[aggre_index] = aggre_sum_[aggre_index] / aggre_count_[aggre_index];
    } break;
    case AttrType::FLOATS: {
      float t = *((float *)value);
      if (t > *(float *)aggre_max_[aggre_index]) {
        *(float *)aggre_max_[aggre_index] = t;
      }
      if (t < *(float *)aggre_min_[aggre_index]) {
        *(float *)aggre_min_[aggre_index] = t;
      }
      aggre_count_[aggre_index]++;
      aggre_sum_[aggre_index] += t;
      aggre_avg_[aggre_index] = aggre_sum_[aggre_index] / aggre_count_[aggre_index];
    } break;
    case AttrType::CHARS: {
      if (strncmp(value, aggre_max_[aggre_index], len) > 0) {
          memcpy(aggre_max_[aggre_index], value, len);
      }
      if (strncmp(value, aggre_min_[aggre_index], len) < 0) {
          memcpy(aggre_min_[aggre_index], value, len);
      }
      aggre_count_[aggre_index]++;
    } break;
    default:
      LOG_PANIC("can't supported aggregate attrtype %d", attr_type);
  }
}

RC AggreSet::finish_aggregate() {
  if (aggre_max_[0] == nullptr) {
    return RC::GENERIC_ERROR;
  }
  for (int i = 0; i < aggres_->size(); i++) {
    switch (aggres_->at(i)->aggre_type) {
      case MAXS: {
        if (aggre_attr_type_[i] == AttrType::INTS) {
          tuple_.add(*((int *)aggre_max_[i]));
        } else if (aggre_attr_type_[i] == AttrType::FLOATS) {
          tuple_.add(*((float *)aggre_max_[i]));
        } else if (aggre_attr_type_[i] == AttrType::CHARS) {
          tuple_.add(aggre_max_[i], strlen(aggre_max_[i]));
        } else {
          LOG_PANIC("can't supported aggregate attrtype %d", aggre_attr_type_[i]);
        }
      } break;
      case MINS: {
        if (aggre_attr_type_[i] == AttrType::INTS) {
          tuple_.add(*((int *)aggre_min_[i]));
        } else if (aggre_attr_type_[i] == AttrType::FLOATS) {
          tuple_.add(*((float *)aggre_min_[i]));
        } else if (aggre_attr_type_[i] == AttrType::CHARS) {
          tuple_.add(aggre_min_[i], strlen(aggre_min_[i]));
        } else {
          LOG_PANIC("can't supported aggregate attrtype %d", aggre_attr_type_[i]);
        }
      } break;
      case AVGS:
        tuple_.add(aggre_avg_[i]);
        break;
      case SUMS:
        tuple_.add(aggre_sum_[i]);
        break;
      case COUNTS:
        tuple_.add(aggre_count_[i]);
        break;
      default:
        LOG_PANIC("can't supported aggregate function");
        return RC::GENERIC_ERROR;
    }
  }
  return RC::SUCCESS;
}

void AggreSet::print(std::ostream &os) const {
  //打印头
  int aggre_num = aggres_->size();
  for (int i = 0; i < aggre_num - 1 ; i++) {
    aggre_type_print(os, aggres_->at(i)->aggre_type);
    os << "(";
    aggre_attr_print(os, i);
    os << ") | ";
  }
  const AggreDesc * last_aggre = aggres_->at(aggre_num - 1);
  aggre_type_print(os, aggres_->at(aggre_num - 1)->aggre_type);
  os << "(";
  aggre_attr_print(os, aggre_num - 1);
  os << ")" << std::endl;
  
  //打印值
  const std::vector<std::shared_ptr<TupleValue>> &values = tuple_.values();
  for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values.begin(), end = --values.end();
      iter != end; ++iter) {
    (*iter)->to_string(os);
    os << " | ";
  }
  values.back()->to_string(os);
  os << std::endl;
}

void AggreSet::aggre_type_print(std::ostream &os, AggreType type) const {
  switch (type) {
    case MAXS:
      os << "max";
      break;
    case MINS:
      os << "min";
      break;
    case AVGS:
      os << "avg";
      break;
    case SUMS:
      os << "sum";
      break;
    case COUNTS:
      os << "count";
      break;
    default:
      LOG_PANIC("can't supported aggregate function");
  }
}

void AggreSet::aggre_attr_print(std::ostream &os, int aggre_index) const {
  const AggreDesc *aggre = aggres_->at(aggre_index);
  if (aggre->is_attr == 1) {
    if (aggre->relation_name != nullptr) {
      os << aggre->relation_name << ".";
    }
    os << aggre->attr_name;
  } else {
    if (aggre->is_star == 1) {
      if (aggre->relation_name != nullptr) {
        os << aggre->relation_name << ".";
      }
      os << aggre->attr_name;
    } else {
      FloatValue(aggre->value).to_string(os);
    }
  }
}

void TupleAggregateUtil::aggregate(const char *record) {
  const TableMeta &table_meta = table_->table_meta();
  // 用该record 更新所有的 aggregate函数结果
  for (int i = 0; i < aggres_.size(); i++) {
    bool is_null = false;
    AggreDesc *cur_aggreDesc = aggres_[i];
    if (cur_aggreDesc->is_attr == 1) {
      const FieldMeta * field_meta = table_meta.field(cur_aggreDesc->attr_name);
      assert(field_meta != nullptr);
      common::Bitmap null_bitmap(const_cast<char *>(record), table_meta.field_num());
      int field_index = table_meta.field_index(cur_aggreDesc->attr_name);
      is_null = null_bitmap.get_bit(field_index);
      switch (field_meta->type()) {
        case INTS:
        case FLOATS:
        case CHARS: 
          aggre_set_.update_aggre_set(i, is_null, field_meta->type(), field_meta->len(), (record + field_meta->offset()));
          break;
        default:
          LOG_PANIC("can't aggregate date at present");
      }
    } else {
      aggre_set_.update_aggre_set(i, is_null, AttrType::FLOATS, sizeof(float), (char *)(&(aggres_[i]->value)));
    }
  }
}

