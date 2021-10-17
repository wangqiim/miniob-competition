/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

// Created by wangyunlai.wyl on 2021/5/18.
//

#ifndef __OBSERVER_STORAGE_COMMON_META_UTIL_H_
#define __OBSERVER_STORAGE_COMMON_META_UTIL_H_

#include <string>
#include <regex>
#include <string.h>

#include <rc.h>

static const char *TABLE_META_SUFFIX = ".table";
static const char *TABLE_META_FILE_PATTERN = ".*\\.table$";
static const char *TABLE_DATA_SUFFIX = ".data";
static const char *TABLE_INDEX_SUFFIX = ".index";

std::string table_meta_file(const char *base_dir, const char *table_name);
std::string index_data_file(const char *base_dir, const char *table_name, const char *index_name);

struct myDate {
	int y;
	int m;
	int d;
	bool operator<(const myDate &rhs) const {
		if (this->y != rhs.y) {
			return this->y < rhs.y;
		}
		if (this->m != rhs.m) {
			return this->m < rhs.m;
		}
		if (this->d != rhs.d) {
			return this->d < rhs.d;
		}
		return false;
	}
};

static const struct myDate dateUpperBound = {2038, 3, 1};

RC check_date(const void *data);

#endif //__OBSERVER_STORAGE_COMMON_META_UTIL_H_
