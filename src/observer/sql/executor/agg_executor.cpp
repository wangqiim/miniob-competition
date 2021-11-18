//
// Created by emrick on 2021/11/15.
//

#include "agg_executor.h"
#include "storage/common/table.h"
#include "aggregate_execution_node.h"

AggExecutor::AggExecutor(ExecutorContext* context, const TupleSchema &output_schema,
                         Executor* executor):Executor(context, output_schema), executor_(executor) {};

RC AggExecutor::init() {
  aht_.init(output_schema_.Get_agg_descs());
  return executor_->init();
}

RC AggExecutor::next(TupleSet &tuple_set, std::vector<Filter*> *filters) {
  tuple_set.clear();
  tuple_set.set_schema(output_schema_);

  TupleSet left_tuple_set;
  executor_->next(left_tuple_set, filters);
  TupleSchema left_output_schema = executor_->output_schema();
  aht_.clear();
  for (const auto &tuple : left_tuple_set.tuples()) {
    AggregateKey agg_key = MakeKey(left_output_schema, &tuple);
    AggregateValue agg_val = MakeVal(left_output_schema, &tuple);
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
      if (output_schema_.Get_agg_descs()[i]->aggre_type == AggreType::AVGS
      && agg_val.aggregates_[i]->Type() != AttrType::UNDEFINED) {
        float avg = agg_val.aggregates_[i]->value() / agg_val.count_[i];
        output_tuple.add(new FloatValue(avg));
      } else {
        output_tuple.add(agg_val.aggregates_[i]);
      }
    }
    tuple_set.add(std::move(output_tuple));

    ++(aht_iterator_);
  }
  
  return RC::SUCCESS;
}

RC AggExecutor::build_agg_output_schema(Db *db, Selects *selects, TupleSchema &schema) {
  assert(selects->aggre_num > 0);
  std::vector<std::shared_ptr<AggreDesc>> aggre_descs;
  // 枚举所有聚集函数
  Table *table;
  for (int i = 0; i < selects->aggre_num; i++) {
    Aggregate select_agg = selects->aggregates[i];
    std::shared_ptr<AggreDesc> aggre_desc(new AggreDesc());
    aggre_desc->aggre_type = select_agg.aggre_type;
    aggre_desc->is_attr = select_agg.is_attr;
    aggre_desc->is_star = 0;
    if (select_agg.is_attr == 1) {
      aggre_desc->relation_name = select_agg.attr.relation_name;
      // 属性：检验字段和表名
      if (aggre_desc->relation_name == nullptr) {
        if (selects->relation_num == 1) {
          aggre_desc->relation_name = selects->relations[0];
        } else {
          return RC::INTERNAL;
        }
      }
      table = db->find_table(aggre_desc->relation_name);
      if (select_agg.attr.attribute_name != 0 && 0 == strcmp("*", select_agg.attr.attribute_name)) {
        if (select_agg.aggre_type != AggreType::COUNTS) {
          // 只有COUNT能匹配*
          return RC::SCHEMA_FIELD_MISSING;
        }
        // 把*当作值"1",来处理，但是依然需要记录属性名为*，方便最后输出表头
        aggre_desc->attr_name = select_agg.attr.attribute_name;
        aggre_desc->is_attr = 0;
        aggre_desc->is_star = 1;
        aggre_desc->value = 1;
        return RC::SUCCESS;
      }
      // 检验聚合表和属性是否合法
      const FieldMeta *field_meta = nullptr;
      field_meta = table->table_meta().field(select_agg.attr.attribute_name);
      if (nullptr == field_meta) {
        return RC::SCHEMA_FIELD_MISSING;
      }
      // 对float和int和char和date字段进行聚集
      if (field_meta->type() == AttrType::UNDEFINED) {
        return RC::SCHEMA_FIELD_MISSING;
      }
      // char和date字段不能进行 sum 和 avg 聚合
      if ((field_meta->type() == AttrType::CHARS || field_meta->type() == AttrType::DATES)
      && (select_agg.aggre_type == AggreType::SUMS || select_agg.aggre_type == AggreType::AVGS)) {
        return RC::SCHEMA_FIELD_MISSING;
      }
      aggre_desc->attr_name = const_cast<char *>(field_meta->name());
    } else {
      // 不考虑aggregate("asd")的情况
      if (select_agg.value.type == AttrType::INTS) {
        aggre_desc->value = *((int *)(select_agg.value.data));
      } else if(select_agg.value.type == AttrType::FLOATS) {
        aggre_desc->value = *((float *)(select_agg.value.data));
      } else {
        return RC::SCHEMA_FIELD_MISSING;
      }
    }

    // 是属性时，属性是否存在，类型是否合法
    // 属性是值时，检验是否是*,只有
    aggre_descs.emplace_back(std::move(aggre_desc));
  }
  for (int i = 0; i < selects->group_num; i++) {
    if (selects->group_bys[i].relation_name == nullptr) {
      if (selects->relation_num == 1) {
        selects->group_bys[i].relation_name = selects->relations[0];
      } else {
        return RC::INTERNAL;
      }
    }
    table = db->find_table(selects->group_bys[i].relation_name);
    TupleSchema::schema_add_field(table ,selects->group_bys[i].attribute_name, schema);
  }
  schema.Set_agg_descs(std::move(aggre_descs));
  return RC::SUCCESS;
}


