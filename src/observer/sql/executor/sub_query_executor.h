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
                   Executor *right_executor,
                   std::vector<Condition> &&multi_table_conditions);

  ~SubQueryExecutor() = default;

  RC init() override;

  RC add_multi_table_filter(const TupleField &field, TupleValue &value, std::vector<Filter*> *filters);

  RC remove_multi_table_filter(std::vector<Filter*> *filters, size_t num);

  RC next(TupleSet &tuple_set, std::vector<Filter*> *filters = nullptr) override;

private:
  Executor *left_executor_;
  RelAttr left_attr_;
  CompOp op_;
  Executor *right_executor_;
  std::vector<Condition> multi_table_conditions_;
};


#endif //MINIDB_SUB_QUERY_EXECUTOR_H
