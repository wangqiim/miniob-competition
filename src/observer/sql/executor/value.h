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

#ifndef __OBSERVER_SQL_EXECUTOR_VALUE_H_
#define __OBSERVER_SQL_EXECUTOR_VALUE_H_

#include <string.h>

#include <string>
#include <ostream>
#include <assert.h>
#include "sql/parser/parse_defs.h"

class TupleValue {
public:
  TupleValue() = default;
  virtual ~TupleValue() = default;

  virtual void to_string(std::ostream &os) const = 0;
  virtual int compare(const TupleValue &other) const = 0;

  AttrType Type() const { return type_;}
  void SetType(AttrType type) { type_ = type; }
private:
  AttrType type_;
};

class IntValue : public TupleValue {
public:
  explicit IntValue(int value) : value_(value) {
    SetType(AttrType::INTS);
  }

  void to_string(std::ostream &os) const override {
    os << value_;
  }

  int compare(const TupleValue &other) const override {
    const IntValue & int_other = (const IntValue &)other;
    return value_ - int_other.value_;
  }

private:
  int value_;
};

class FloatValue : public TupleValue {
public:
  explicit FloatValue(float value) : value_(value) {
    SetType(AttrType::FLOATS);
  }

  // https://github.com/wangqiim/miniob/issues/2
  // TODO(wq): 输出需要格式化
  void to_string(std::ostream &os) const override {
    char s[20] = {0};
    sprintf(s, "%.2f", value_);
    for (int i = 19; i >= 0; i--) {
      if (s[i] == '0' || s[i] == 0) {
        s[i] = 0;
        continue;
      }
      if (s[i] == '.') {
        s[i] = 0;
      }
      break;
    }
    os << s;
  }

  int compare(const TupleValue &other) const override {
    const FloatValue & float_other = (const FloatValue &)other;
    float result = value_ - float_other.value_;
    if (-1e-5 < result && result < 1e-5) {
      return 0;
    }
    if (result > 0) { // 浮点数没有考虑精度问题
      return 1;
    }
    if (result < 0) {
      return -1;
    }
    return 0;
  }
private:
  float value_;
};

class StringValue : public TupleValue {
public:
  StringValue(const char *value, int len) : value_(value, len){
    SetType(AttrType::CHARS);
  }
  explicit StringValue(const char *value) : value_(value) {
  }

  void to_string(std::ostream &os) const override {
    os << value_;
  }

  int compare(const TupleValue &other) const override {
    const StringValue &string_other = (const StringValue &)other;
    return strcmp(value_.c_str(), string_other.value_.c_str());
  }
private:
  std::string value_;
};

class NullValue : public TupleValue {
public:
  NullValue() {
    SetType(AttrType::UNDEFINED);
  }

  void to_string(std::ostream &os) const override {
    os << "null";
  }

  int compare(const TupleValue &other) const override {
    // TODO(wq): 哪里用到??
    assert(false);
    return -1;
  }
};


#endif //__OBSERVER_SQL_EXECUTOR_VALUE_H_
