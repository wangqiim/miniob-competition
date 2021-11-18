#include "sql/executor/exp_execution_node.h"
#include "sql/executor/util.h"

RC ExpExeNode::init(TupleSchema &&output_tuple_schema, TupleSet &&tuple_set, CompositeExpressionFilter *condition_filter,
                    const std::map<std::string, std::map<std::string, int>> &field_index) {
    output_tuple_schema_ = output_tuple_schema;
    condition_filter_ = condition_filter;
    tuple_set_ = std::move(tuple_set);
    field_index_ = &field_index;
    return RC::SUCCESS;
}

RC ExpExeNode::execute(TupleSet &output_tuple_set) {
    RC rc = RC::SUCCESS;
    output_tuple_set.clear();
    output_tuple_set.set_schema(output_tuple_schema_);
    std::vector<Tuple> &tuples = const_cast<std::vector<Tuple> &>(tuple_set_.tuples());
    for (const Tuple &tuple : tuples) {
        if (condition_filter_->filter(tuple)) {
            Tuple output_tuple;
            // 1. 构造普通字段
            for (const auto & field : output_tuple_schema_.fields()) {
                int value_index = field_index_->at(field.table_name()).at(field.field_name());
                output_tuple.add(tuple.get_pointer(value_index));
            }
            // 2. 构造表达式字段
            for (const auto & exp : output_tuple_schema_.get_exps()) {
                std::shared_ptr<TupleValue> value;
                rc = AstUtil::Calculate(value, tuple, *field_index_, exp);
                assert(rc == RC::SUCCESS);
                output_tuple.add(value);
            }
            output_tuple_set.add(std::move(output_tuple));
        }
    }
    return RC::SUCCESS;
}

// output_schema 待打印的表头(已经填充好tuple_field字段，需要填充expression字段)
RC create_expression_executor(const Selects &selects, ExpExeNode &exp_exe_node, TupleSet &&tuple_set, TupleSchema &output_schema, const std::map<std::string, std::map<std::string, int>> &field_index) {
    // 找到带有表达式的过滤条件
    std::vector<DefaultExpressionFilter *> condition_filters;
    for (size_t i = 0; i < selects.condition_num; i++) {
        const Condition &condition = selects.conditions[i];
        if (condition.left_ast == nullptr && condition.right_ast == nullptr) {
            continue;
        }
        CartesianConDesc left_cond{-1, -1, nullptr, 0, {}};
        CartesianConDesc right_cond{-1, -1, nullptr, 0, {}};
        if (condition.left_ast) {
            left_cond.exp_ast = condition.left_ast;
        } else if (condition.left_is_attr) {
            const char *table_name = (condition.left_attr.relation_name == nullptr ? selects.relations[0] : condition.left_attr.relation_name);
            left_cond.value_index = field_index.at(table_name).at(condition.left_attr.attribute_name);
        } else {
            left_cond.value = condition.left_value;
        }
        if (condition.right_ast) {
            right_cond.exp_ast = condition.right_ast;
        } else if (condition.right_is_attr) {
            const char *table_name = (condition.right_attr.relation_name == nullptr ? selects.relations[0] : condition.right_attr.relation_name);
            right_cond.value_index = field_index.at(table_name).at(condition.right_attr.attribute_name);
        } else {
            right_cond.value = condition.right_value;
        }
        auto *condition_filter = new DefaultExpressionFilter();
        condition_filter->init(left_cond, right_cond, condition.comp, field_index);
        condition_filters.push_back(condition_filter);
    }
    CompositeExpressionFilter *composite_condition_filter = new CompositeExpressionFilter();
    composite_condition_filter->init(std::move(condition_filters), condition_filters.size() > 0);

    // 构造schema表头中的表达式
    for (int i = 0; i < selects.attr_exp_num; i++) {
        output_schema.add_exp(selects.attributes_exp[i]);
    }
    
    return exp_exe_node.init(std::move(output_schema), std::move(tuple_set), composite_condition_filter, field_index);
}