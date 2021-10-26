//
// Created by emrick on 2021/10/27.
//

#include "scan_executor.h"
#include <vector>

ScanExecutor::ScanExecutor(ExecutorContext* context,
                           Table *table,
                           const TupleSchema &output_schema,
                           std::vector<Filter*> &&condition_filters,
                           bool ban_all):
                           Executor(context, output_schema),
                           table_(table),
                           condition_filters_(std::move(condition_filters)),
                           ban_all_(ban_all){}

RC ScanExecutor::init() {
  RC rc;
  for (const auto &filter : condition_filters_) {
    rc = filter->bind_table(table_);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }
  return RC::SUCCESS;
}

void record_saver(const char *data, void *context) {
  TupleRecordConverter *converter = (TupleRecordConverter *)context;
  converter->add_record(data);
}

RC ScanExecutor::next(TupleSet &tuple_set, std::vector<Filter*> *filters) {
  tuple_set.clear();
  tuple_set.set_schema(output_schema_);
  if (ban_all_) {
    return RC::SUCCESS;
  }
  std::vector<Filter *> all_filters;
  if (filters != nullptr) {
    for(const auto &filter : *filters) {
      filter->bind_table(table_);
      all_filters.push_back(filter);
    }
  }
  for (const auto & filter_: condition_filters_) {
    all_filters.push_back(filter_);
  }

  CompositeConditionFilter condition_filter;
  condition_filter.init((const ConditionFilter **)all_filters.data(), all_filters.size());

  TupleRecordConverter converter(table_, tuple_set);
  return table_->scan_record(exe_ctx_->get_trx(), &condition_filter, -1, (void *)&converter, record_saver);
}
