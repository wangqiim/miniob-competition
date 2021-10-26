//
// Created by emrick on 2021/10/27.
//

#ifndef MINIDB_INNER_JOIN_EXECUTOR_H
#define MINIDB_INNER_JOIN_EXECUTOR_H

#include "storage/common/table.h"
#include "sql/executor/executor.h"
#include "tuple.h"


class InnerJoinExecutor : public Executor {
public:
  InnerJoinExecutor(ExecutorContext* context,
                    const TupleSchema &output_schema,
                    Executor *left_executor,
                    Executor *right_executor,
                    std::vector<Filter*> condition_filters);


  virtual ~InnerJoinExecutor() = default;

  RC init() override;

  RC next(TupleSet &tuple_set, std::vector<Filter*> *filters = nullptr) override;

private:
  TupleSchema  output_schema_;
  Executor *left_executor_;
  Executor *right_executor_;
  std::vector<Filter *> condition_filters_;
};


#endif //MINIDB_INNER_JOIN_EXECUTOR_H
