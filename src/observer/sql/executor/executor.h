//
// Created by emrick on 2021/10/27.
//
#ifndef MINIDB_EXECUTOR_H
#define MINIDB_EXECUTOR_H


#include <storage/common/condition_filter.h>
#include "tuple.h"

class ExecutorContext {
public:
  explicit ExecutorContext(): trx_(nullptr) {}

  Trx * get_trx() {
    return trx_;
  }
private:
  Trx *trx_ = nullptr;

};

class Executor {
public:
  explicit Executor(ExecutorContext* context, const TupleSchema& output_schema): exe_ctx_(context), output_schema_(output_schema) {}
  virtual ~Executor() = default;

  virtual RC init() = 0;

  /**
   * 每次查询一批记录
   * @param tuple_set 返回的查询结果，所有结果属于同一个Table
   * @param filters 可以作为临时加入的查询条件，一般该条件在父节点执行过程中被确定
   */
  virtual RC next(TupleSet &tuple_set, std::vector<Filter*> *filters = nullptr) = 0;

  TupleSchema output_schema() {
    return output_schema_;
  }

  void set_output_schema(TupleSchema &&output_schema) {
    output_schema_ = output_schema;
  }

protected:
  ExecutorContext *exe_ctx_;
  TupleSchema  output_schema_;
};


#endif //MINIDB_EXECUTOR_H