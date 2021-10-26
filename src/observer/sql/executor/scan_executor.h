//
// Created by emrick on 2021/10/27.
//

#ifndef MINIDB_SCAN_EXECUTOR_H
#define MINIDB_SCAN_EXECUTOR_H

#include "storage/common/table.h"
#include "sql/executor/executor.h"
#include "tuple.h"
#include <vector>

class ScanExecutor : public Executor {
public:
  ScanExecutor(ExecutorContext* context, Table *table, const TupleSchema &output_schema, std::vector<Filter*> &&condition_filters, bool ban_all);

 ~ScanExecutor() = default;

  RC init() override;

  RC next(TupleSet &tuple_set, std::vector<Filter*> *filters = nullptr) override;

private:
  Table * table_;
  std::vector<Filter *> condition_filters_;
  bool ban_all_ = false;
};


#endif //MINIDB_SCAN_EXECUTOR_H
