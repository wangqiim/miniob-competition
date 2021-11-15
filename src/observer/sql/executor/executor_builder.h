//
// Created by emrick on 2021/10/31.
//

#ifndef MINIDB_EXECUTOR_BUILDER_H
#define MINIDB_EXECUTOR_BUILDER_H


#include <sql/parser/parse_defs.h>
#include <event/session_event.h>
#include <storage/default/default_handler.h>
#include "rc.h"
#include "executor.h"
#include "scan_executor.h"
#include "sub_query_executor.h"

class ExecutorBuilder {
public:
  ExecutorBuilder(const char *db, Query *sql, SessionEvent *session_event):
  db_(DefaultHandler::get_default().find_db(db)), sql_(sql), session_event_(session_event) {}

  ExecutorBuilder(Db *db): db_(db), sql_(nullptr), session_event_(nullptr) {}

  Executor* build();

  Executor* build(Selects *selects);

  Executor* build_select_executor(Selects *selects);

  Executor* build_join_executor(Executor *executor, Selects *selects);

  Executor *build_sub_query_executor(Executor *executor, char *table_name, Condition conditions[], size_t condition_num);

  TupleSchema build_output_schema(Selects *selects);



private:
  Db *db_;
  Query *sql_;
  SessionEvent *session_event_;
};



#endif //MINIDB_EXECUTOR_BUILDER_H
