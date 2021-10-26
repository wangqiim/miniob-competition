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
                   const TupleSchema &output_schema,
                   Executor *current_executor,
                   Executor *sub_executor,
                   std::vector<Filter*> condition_filters);

  ~SubQueryExecutor() = default;

  RC init() override;

  RC next(TupleSet &tuple_set, std::vector<Filter*> *filters = nullptr) override;

private:
  Executor *current_executor_;
  Executor *sub_executor_;
  std::vector<Filter *> condition_filters_;
};


#endif //MINIDB_SUB_QUERY_EXECUTOR_H
