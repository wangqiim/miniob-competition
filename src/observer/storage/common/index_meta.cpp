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
// Created by wangyunlai.wyl on 2021/5/18.
//

#include "storage/common/index_meta.h"
#include "storage/common/field_meta.h"
#include "storage/common/table_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "rc.h"
#include "json/json.h"

const static Json::StaticString INDEX_NAME("index_name");
const static Json::StaticString INDEX_FIELD_NAMES("index_field_names");
const static Json::StaticString FIELD_NAME("field_name");

RC IndexMeta::init(const char *name, std::vector<const FieldMeta *> fields) {
  if (nullptr == name || common::is_blank(name)) {
    return RC::INVALID_ARGUMENT;
  }

  name_ = name;
  field_.clear();
  for (const FieldMeta *field : fields) {
    field_.push_back(field->name());
  }
  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const {
  json_value[INDEX_NAME] = name_;
  Json::Value fields_value;
  for (const std::string &field : field_) {
    Json::Value field_value;
    field_value[FIELD_NAME] = field;
    fields_value.append(std::move(field_value));
  }
  json_value[INDEX_FIELD_NAMES] = std::move(fields_value);
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index) {
  const Json::Value &name_value = json_value[INDEX_NAME];
  const Json::Value &fields_values = json_value[INDEX_FIELD_NAMES];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }
  if (!fields_values.isArray()) {
    LOG_ERROR("Invalid index_fields_metas, json value=%s", fields_values.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }
  RC rc = RC::SUCCESS;
  int field_num = fields_values.size();
  std::vector<const FieldMeta *> fields(field_num);
  for (int i = 0; i < field_num; i++) {
    const Json::Value &field_name_value = fields_values[i];
    if (!field_name_value[FIELD_NAME].isString()) {
      LOG_ERROR("Field name is not a string. json value=%s", field_name_value.toStyledString().c_str());
      return RC::GENERIC_ERROR;
    }
    const FieldMeta *field = table.field(field_name_value[FIELD_NAME].asCString());
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to deserialize index meta. index name =%s", name_value.asCString());
      return RC::GENERIC_ERROR;
    }
    fields[i] = field;
  }
  return index.init(name_value.asCString(), fields);
}

const char *IndexMeta::name() const {
  return name_.c_str();
}

const char *IndexMeta::field() const {
  return field_[0].c_str();
}

const std::vector<std::string> &IndexMeta::fields() const {
  return field_;
}

void IndexMeta::desc(std::ostream &os) const {
  os << "index name=" << name_
      << ", field=" << field_[0];
}