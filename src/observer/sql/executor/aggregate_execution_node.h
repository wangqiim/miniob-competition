
#ifndef MINIDB_AGGEXECUTOR_NODE_H
#define MINIDB_AGGEXECUTOR_NODE_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <limits.h>
#include "storage/common/table.h"
#include "sql/executor/execution_node.h"

struct AggregateKey {
  std::vector<std::shared_ptr<TupleValue>> group_bys_;

  bool operator<(const AggregateKey &other) const {
		int ret = 0;
    for (uint32_t i = 0; i < other.group_bys_.size(); i++) {
      if ((ret = group_bys_[i]->compare(*(other.group_bys_[i]))) != 0) {
				return ret < 0;
      }
    }
    return ret < 0;
  }
};

struct AggregateValue {
	// max or min or sum or count
  std::vector<std::shared_ptr<TupleValue>> aggregates_;
	// 没什么好办法，由于avg的存在，一个值没法表示所有的聚合函数类型，所以多存一个count,用sum/count表示avg
  std::vector<int> count_;

};

/**
 * A simplified hash table that has all the necessary functionality for aggregations.
 * 哈希函数不太好搞， 用treeMap代替
 */
class SimpleAggregationHashTable {
 public:
 SimpleAggregationHashTable() = default;

  void init(const std::vector<std::shared_ptr<AggreDesc>> &agg_descs) { agg_descs_ = agg_descs; }

  /** @return the initial aggregrate value for this aggregation executor */
  AggregateValue GenerateInitialAggregateValue() {
    std::vector<std::shared_ptr<TupleValue>> values;
    std::vector<int> counts(agg_descs_.size(), 0);
    for (int i = 0 ; i < agg_descs_.size(); i++) {
      const AggreDesc *agg_desc = agg_descs_[i].get();
      switch (agg_desc->aggre_type) {
        case AggreType::COUNTS:
          values.emplace_back(new FloatValue(0));
          break;
        case AggreType::SUMS:
          values.emplace_back(new NullValue());
          break;
        case AggreType::MINS:
          values.emplace_back(new NullValue());
          break;
        case AggreType::MAXS:
          values.emplace_back(new NullValue());
          break;
        case AggreType::AVGS:
          values.emplace_back(new NullValue());
          break;
				default:
					assert(false);
      }
    }
    return {values, counts};
  }

  void CombineAggregateValues(AggregateValue *result, const AggregateValue &input) {
    for (uint32_t i = 0; i < agg_descs_.size(); i++) {
      if (input.aggregates_[i]->Type() == AttrType::UNDEFINED) { // null
        continue;
      }
      result->count_[i]++;
      switch (agg_descs_[i]->aggre_type) {
        case AggreType::COUNTS:
          result->aggregates_[i]->plus(1);
          break;
        case AggreType::SUMS:
          if (result->aggregates_[i]->Type() == AttrType::UNDEFINED) {
            result->aggregates_[i] = std::shared_ptr<TupleValue>(new FloatValue(0));
          }
          result->aggregates_[i]->plus(input.aggregates_[i]->value());
          break;
        case AggreType::MAXS:
					if (result->aggregates_[i]->Type() == AttrType::UNDEFINED ||
							input.aggregates_[i]->compare(*(result->aggregates_[i])) > 0) {
						result->aggregates_[i] = input.aggregates_[i];
					}
          break;
        case AggreType::MINS:
					if (result->aggregates_[i]->Type() == AttrType::UNDEFINED ||
							input.aggregates_[i]->compare(*(result->aggregates_[i])) < 0) {
						result->aggregates_[i] = input.aggregates_[i];
					}
          break;
				case AggreType::AVGS:
          if (result->aggregates_[i]->Type() == AttrType::UNDEFINED) {
            result->aggregates_[i] = std::shared_ptr<TupleValue>(new FloatValue(0));
          }
          result->aggregates_[i]->plus(input.aggregates_[i]->value());
					break;
				default:
					assert(false);
      }
    }
  }

  /**
   * Inserts a value into the hash table and then combines it with the current aggregation.
   * @param agg_key the key to be inserted
   * @param agg_val the value to be inserted
   */
  void InsertCombine(const AggregateKey &agg_key, const AggregateValue &agg_val) {
    if (ht_.count(agg_key) == 0) {
      ht_.insert({agg_key, GenerateInitialAggregateValue()});
    }
    CombineAggregateValues(&ht_[agg_key], agg_val);
  }

  /**
   * An iterator through the simplified aggregation hash table.
   */
  class Iterator {
   public:
    Iterator() = default;
    /** Creates an iterator for the aggregate map. */
    explicit Iterator(std::map<AggregateKey, AggregateValue>::const_iterator iter) : iter_(iter) {}

    /** @return the key of the iterator */
    const AggregateKey &Key() { return iter_->first; }

    /** @return the value of the iterator */
    const AggregateValue &Val() { return iter_->second; }

    /** @return the iterator before it is incremented */
    Iterator &operator++() {
      ++iter_;
      return *this;
    }

    /** @return true if both iterators are identical */
    bool operator==(const Iterator &other) { return this->iter_ == other.iter_; }

    /** @return true if both iterators are different */
    bool operator!=(const Iterator &other) { return this->iter_ != other.iter_; }

   private:
    /** Aggregates map. */
    std::map<AggregateKey, AggregateValue>::const_iterator iter_;
  };

  /** @return iterator to the start of the hash table */
  Iterator Begin() { return Iterator{ht_.cbegin()}; }

  /** @return iterator to the end of the hash table */
  Iterator End() { return Iterator{ht_.cend()}; }

 private:
  /** The hash table is just a map from aggregate keys to aggregate values. */
  std::map<AggregateKey, AggregateValue> ht_{};
  /** The aggregate expressions that we have. */
  std::vector<std::shared_ptr<AggreDesc>> agg_descs_;
};

/**
 * AggregationExecutor executes an aggregation operation (e.g. COUNT, SUM, MIN, MAX) on the tuples of a child executor.
 */
class AggregationExeNode : public ExecutionNode {
 public:
  AggregationExeNode() = default;
  ~AggregationExeNode() = default;

  RC init(Trx *trx, Table *table, TupleSchema &&group_bys, TupleSet &&tuple_set);

  RC execute(TupleSet &output_tuple_set) override;

  /** @return the tuple as an AggregateKey */
  AggregateKey MakeKey(const Tuple *tuple) {
    std::vector<std::shared_ptr<TupleValue>> keys;
    for (const auto &field : group_bys_.fields()) {
			int index = tuple_set_.get_schema().table_field_index().at(field.table_name()).at(field.field_name());
			keys.emplace_back(tuple->values()[index]);
    }
    return {keys};
  }

  /** @return the tuple as an AggregateValue */
  AggregateValue MakeVal(const Tuple *tuple) {
    std::vector<std::shared_ptr<TupleValue>> vals;
		std::vector<int> counts(agg_descs_.size(), 1);
    for (int i = 0 ; i < agg_descs_.size(); i++) {
      const AggreDesc *agg_desc = agg_descs_[i].get();
			if (agg_desc->is_attr) {
				// agg(relation_name,attr_name)
				const char *table_name = agg_desc->relation_name;
				if (table_name == nullptr) {
					table_name = table_->table_meta().name();
				}
				int index = tuple_set_.get_schema().table_field_index().at(table_name).at(agg_desc->attr_name);
				vals.emplace_back(tuple->values()[index]);
			} else {
				// agg(*)
				// agg(12.3)
				vals.emplace_back(new FloatValue(agg_desc->value));
			}
    }
    return {vals, counts};
  }

 private:
  Trx *trx_ = nullptr;
	Table *table_; // 如果是单表,AggreDesc中无表名,为了找索引,用table来辅助找field的下标索引
  TupleSchema group_bys_; //通过这些字段聚集，如果为空说明无group by
	std::vector<std::shared_ptr<AggreDesc>> agg_descs_; // 所有的聚集函数
  /* aggregate on this tuple_set_ */
  TupleSet tuple_set_;
  /** Simple aggregation hash table. */
  SimpleAggregationHashTable aht_{};
  /** Simple aggregation hash table iterator. */
  SimpleAggregationHashTable::Iterator aht_iterator_;
};

#endif