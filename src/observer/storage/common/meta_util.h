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
#include <assert.h>
#include <string.h>

#include <rc.h>
#include "sql/parser/parse_defs.h"

static const char *TABLE_META_SUFFIX = ".table";
static const char *TABLE_META_FILE_PATTERN = ".*\\.table$";
static const char *TABLE_DATA_SUFFIX = ".data";
static const char *TABLE_INDEX_SUFFIX = ".index";

std::string table_meta_file(const char *base_dir, const char *table_name);
std::string index_data_file(const char *base_dir, const char *table_name, const char *index_name);

// 该类实现对Date attr的核对和格式化
class DateUtil {
public:
	/**
	 * @param y,m,d 日期上界
	 */
	DateUtil(int y, int m, int d) : uy_(y), um_(m), ud_(d) {
		ly_ = 1970; // 日期下界
	}

	RC Check_and_format_date(void *data);

private:
	// 日期范围[1970-01-01 ~ 2038-03-01)
	bool check_dateRange(int y, int m, int d);

	int uy_;
	int um_;
	int ud_;
	int ly_; // 日期下界1970-01-01
};

DateUtil *theGlobalDateUtil();

#endif //__OBSERVER_STORAGE_COMMON_META_UTIL_H_
