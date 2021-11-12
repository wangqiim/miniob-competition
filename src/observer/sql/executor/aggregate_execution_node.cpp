#include <sql/executor/aggregate_execution_node.h>

void AggregationExeNode::aggre_type_print(std::ostream &os, AggreType type) {
  switch (type) {
    case MAXS:
      os << "max";
      break;
    case MINS:
      os << "min";
      break;
    case AVGS:
      os << "avg";
      break;
    case SUMS:
      os << "sum";
      break;
    case COUNTS:
      os << "count";
      break;
    default:
			assert(false);
  }
}

void AggregationExeNode::aggre_attr_print(std::ostream &os, int aggre_index) {
  const AggreDesc *aggre = agg_descs_.at(aggre_index);
  if (aggre->is_attr == 1) {
    if (aggre->relation_name != nullptr) {
      os << aggre->relation_name << ".";
    }
    os << aggre->attr_name;
  } else {
    if (aggre->is_star == 1) {
      if (aggre->relation_name != nullptr) {
        os << aggre->relation_name << ".";
      }
      os << aggre->attr_name;
    } else {
      FloatValue(aggre->value).to_string(os);
    }
  }
}

RC AggregationExeNode::init(Trx *trx, Table *table, TupleSchema &&group_bys, TupleSet &&tuple_set,
							std::vector<AggreDesc *> &agg_descs, std::ostream &os) {
	trx_ = trx;
	table_ = table;
	group_bys_ = group_bys;
	tuple_set_ = std::move(tuple_set);
	agg_descs_ = agg_descs;
	aht_.init(agg_descs);
	os_ = &os;
	return RC::SUCCESS;
}

// TODO(wq): null
RC AggregationExeNode::execute(TupleSet &output_tuple_set) {
  output_tuple_set.clear();
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
			if (agg_descs_[i]->aggre_type == AggreType::AVGS) {
				float avg = agg_val.aggregates_[i]->value() / agg_val.count_[i];
				output_tuple.add(new FloatValue(avg));
			} else {
				output_tuple.add(agg_val.aggregates_[i]);
			}
		}
		output_tuple_set.add(std::move(output_tuple));

		++(aht_iterator_);
	}

	//TODO(wq): 打印的这段逻辑应该拿出来
	// 打印头
	group_bys_.print(*os_, true, false);

	int aggre_num = agg_descs_.size();
	for (int i = 0; i < aggre_num - 1 ; i++) {
		aggre_type_print(*os_, agg_descs_.at(i)->aggre_type);
		(*os_) << "(";
		aggre_attr_print(*os_, i);
		(*os_) << ") | ";
	}
	const AggreDesc * last_aggre = agg_descs_.at(aggre_num - 1);
	aggre_type_print((*os_), agg_descs_.at(aggre_num - 1)->aggre_type);
	(*os_) << "(";
	aggre_attr_print((*os_), aggre_num - 1);
	(*os_) << ")" << std::endl;
	// 打印值
	output_tuple_set.print(*os_, true);

	return RC::SUCCESS;
}