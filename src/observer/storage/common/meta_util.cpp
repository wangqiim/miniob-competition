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

#include "storage/common/meta_util.h"

std::string table_meta_file(const char *base_dir, const char *table_name) {
  return std::string(base_dir) + "/" + table_name + TABLE_META_SUFFIX;
}

std::string index_data_file(const char *base_dir, const char *table_name, const char *index_name) {
  return std::string(base_dir) + "/" + table_name + "-" + index_name + TABLE_INDEX_SUFFIX;
}

RC check_date(const void *data) {
	const char *datas = reinterpret_cast<const char *>(data);
	if (!std::regex_match(datas, std::regex("^[0-9]{0,4}-[0-9]{1,2}-[0-9]{1,2}$"))) {
	return RC::SCHEMA_FIELD_TYPE_MISMATCH;
	}
	int y = atoi(datas);
	datas = strchr(datas, '-');
	int m = atoi(datas + 1);
	datas = strchr(datas, '-');
	int d = atoi(datas + 1);
	
	if (y < 0 || m < 0 || d < 0) {
	return RC::SCHEMA_FIELD_TYPE_MISMATCH;
	}

	// https://blog.csdn.net/qq_45672975/article/details/104353064
	int leapyear = 0;
	if ((y % 400 == 0) || (y % 4 == 0 && y % 400 != 0)){
		leapyear = 1; 
	}
	if (m > 12 || m < 1 || d > 31 || d < 1 ||
			(m == 4 || m == 6 || m == 9 || m == 11) && (d > 30) || 
			(m == 2) && (d > 28 + leapyear)) {
		return RC::SCHEMA_FIELD_TYPE_MISMATCH;
	}
	struct myDate dt{y, m, d};
	if (!(dt < dateUpperBound)) {
		return RC::SCHEMA_FIELD_TYPE_MISMATCH;
	}
	
  return RC::SUCCESS;
}
