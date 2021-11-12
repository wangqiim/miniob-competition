#include <sql/executor/aggregate_execution_node.h>

RC AggregationExeNode::init(Trx *trx, Table *table, TupleSchema &&group_bys, TupleSet &&tuple_set) {
	trx_ = trx;
	table_ = table;
	group_bys_ = group_bys;
	tuple_set_ = std::move(tuple_set);
	agg_descs_ = group_bys.Get_agg_descs();
	aht_.init(agg_descs_);
	return RC::SUCCESS;
}

RC AggregationExeNode::execute(TupleSet &output_tuple_set) {
  output_tuple_set.clear();
  output_tuple_set.set_schema(group_bys_);
  std::vector<Tuple> &tuples = const_cast<std::vector<Tuple> &>(tuple_set_.tuples());
	for (const Tuple &tuple : tuples) {
    AggregateKey agg_key = MakeKey(&tuple);
    AggregateValue agg_val = MakeVal(&tuple);
    aht_.InsertCombine(agg_key, agg_val);
	}
	aht_iterator_ = aht_.Begin();
	while (aht_iterator_ != aht_.End()) {
    Tuple output_tuple;
    const AggregateKey &agg_key = aht_iterator_.Key();
    const AggregateValue &agg_val = aht_iterator_.Val();

    for(int i = 0; i < agg_key.group_bys_.size(); i++) {
      output_tuple.add(agg_key.group_bys_[i]);
    }
		for (int i = 0; i < agg_val.aggregates_.size(); i++) {
			if (agg_descs_[i]->aggre_type == AggreType::AVGS 
          && agg_val.aggregates_[i]->Type() != AttrType::UNDEFINED) {
				float avg = agg_val.aggregates_[i]->value() / agg_val.count_[i];
				output_tuple.add(new FloatValue(avg));
			} else {
				output_tuple.add(agg_val.aggregates_[i]);
			}
		}
		output_tuple_set.add(std::move(output_tuple));

		++(aht_iterator_);
	}
  
	return RC::SUCCESS;
}