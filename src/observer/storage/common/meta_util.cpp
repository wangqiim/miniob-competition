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

bool DateUtil::cmp_dateUpperBound(int y, int m, int d) {
	if (y != y_) {
		return y < y_;
	}
	if (m != m_) {
		return m < m_;
	}
	if (d != d_) {
		return d < d_;
	}
	return false;
}

RC DateUtil::Check_and_format_date(void **data) {
	// 1. check date valid
	char *datas = reinterpret_cast<char *>(*data);
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
	if (!cmp_dateUpperBound(y, m, d)) {
		return RC::SCHEMA_FIELD_TYPE_MISMATCH;
	}
	// 2. date format
	char *tp = alloc();
	sprintf(tp, "%04d", y);
	sprintf(tp + 5, "%02d", m);
	sprintf(tp + 8, "%02d", d);
	tp[4] = tp[7] = '-';
	tp[10] = tp[11] = '\0';
	*data = tp;
	return RC::SUCCESS;
}

DateUtil *theGlobalDateUtil() {  
	static int UPBOUNDYEAR = 2038;
	static int UPBOUNDMONTH = 3;
	static int UPBOUNDDAY = 1;
	static DateUtil *instance = new DateUtil(UPBOUNDYEAR, UPBOUNDMONTH, UPBOUNDDAY, DATESSIZE, 1000);
	return instance;
}
