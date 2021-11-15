//
// Created by emrick on 2021/10/27.
//

#ifndef MINIDB_SUB_QUERY_EXECUTOR_H
#define MINIDB_SUB_QUERY_EXECUTOR_H

#include "storage/common/table.h"
#include "sql/executor/executor.h"
#include "tuple.h"
#include <vector>

class SubQueryExecutor : public Executor {

public:
  SubQueryExecutor(ExecutorContext* context,
                   Executor *left_executor,
                   RelAttr left_attr,
                   CompOp op,
                   Executor *right_executor);

  ~SubQueryExecutor() = default;

  RC init() override;

  RC next(TupleSet &tuple_set, std::vector<Filter*> *filters = nullptr) override;

private:
  Executor *left_executor_;
  RelAttr left_attr_;
  CompOp op_;
  Executor *right_executor_;
};


#endif //MINIDB_SUB_QUERY_EXECUTOR_H
