//
// Created by emrick on 2021/10/27.
//

#ifndef MINIDB_INNER_JOIN_EXECUTOR_H
#define MINIDB_INNER_JOIN_EXECUTOR_H

#include "storage/common/table.h"
#include "sql/executor/executor.h"
#include "tuple.h"
#include <vector>


class NestLoopJoinExecutor : public Executor {
public:
  NestLoopJoinExecutor(ExecutorContext* context,
                       const TupleSchema &output_schema,
                       Executor *left_executor,
                       Executor *right_executor,
                       std::vector<Filter*> condition_filters,
                       bool ban_all=false);

  ~NestLoopJoinExecutor() = default;

  RC init() override;

  RC next(TupleSet &tuple_set, std::vector<Filter*> *filters = nullptr) override;

private:
  Executor *left_executor_;
  Executor *right_executor_;
  std::vector<Filter *> condition_filters_;
  bool ban_all_ = false;
};


#endif //MINIDB_INNER_JOIN_EXECUTOR_H
