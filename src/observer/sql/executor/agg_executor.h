//
// Created by emrick on 2021/11/15.
//

#ifndef MINIDB_AGGEXECUTOR_H
#define MINIDB_AGGEXECUTOR_H


#include "executor.h"
#include "aggregate_execution_node.h"


class AggExecutor : public Executor {
public:
  AggExecutor(ExecutorContext* context, const TupleSchema &output_schema, Executor* executor);

  ~AggExecutor() = default;

  RC init() override;

  RC next(TupleSet &tuple_set, std::vector<Filter*> *filters = nullptr) override;

  /** @return the tuple as an AggregateKey */
  AggregateKey MakeKey(TupleSchema &left_tuple_schema, const Tuple *tuple) {
    std::vector<std::shared_ptr<TupleValue>> keys;
    for (const auto &field : output_schema_.fields()) {
      int index = left_tuple_schema.table_field_index().at(field.table_name()).at(field.field_name());
      keys.emplace_back(tuple->values()[index]);
    }
    return {keys};
  }

  /** @return the tuple as an AggregateValue */
  AggregateValue MakeVal(TupleSchema &left_tuple_schema, const Tuple *tuple) {
    std::vector<std::shared_ptr<TupleValue>> vals;
    std::vector<int> counts(output_schema_.Get_agg_descs().size(), 1);
    for (int i = 0 ; i < output_schema_.Get_agg_descs().size(); i++) {
      const AggreDesc *agg_desc = output_schema_.Get_agg_descs()[i].get();
      if (agg_desc->is_attr) {
        // agg(relation_name,attr_name)
        char *table_name = agg_desc->relation_name;
        int index = left_tuple_schema.table_field_index().at(table_name).at(agg_desc->attr_name);
        vals.emplace_back(tuple->values()[index]);
      } else {
        // agg(*)
        // agg(12.3)
        vals.emplace_back(new FloatValue(agg_desc->value));
      }
    }
    return {vals, counts};
  }

  static RC build_agg_output_schema(Table *table, Selects *selects, TupleSchema &schema);

private:

  Executor *executor_;
  /** Simple aggregation hash table. */
  SimpleAggregationHashTable aht_{};
  /** Simple aggregation hash table iterator. */
  SimpleAggregationHashTable::Iterator aht_iterator_;
};


#endif //MINIDB_AGGEXECUTOR_H
