#include "sql/executor/util.h"
#include <sstream>

const std::map<std::string, std::map<std::string, int>> *TupleSortUtil::field_index_ = nullptr;
const TupleSchema *TupleSortUtil::order_by_schema_ = nullptr;

// tuple计算expression应该一定是正确的，condition计算expresion有可能错，此时相当于一条false条件
RC AstUtil::Calculate(std::shared_ptr<TupleValue> &value, const Tuple &tuple, const std::map<std::string, std::map<std::string, int>> &field_index, ast *a) {
    if (a == nullptr) {
        value = std::shared_ptr<TupleValue>(new FloatValue(0));
        return RC::SUCCESS;
    }
    RC rc = RC::SUCCESS;
    switch (a->nodetype) {
    case NodeType::ADDN: {
        std::shared_ptr<TupleValue> lvalue, rvalue;
        rc = Calculate(lvalue, tuple, field_index, a->l);
        if (rc != RC::SUCCESS) {
            return rc;
        }
        rc = Calculate(rvalue, tuple, field_index, a->r);
        if (rc != RC::SUCCESS) {
            return rc;
        }
        value = std::shared_ptr<TupleValue>(new FloatValue(lvalue->value() + rvalue->value()));
    } break;
    case NodeType::SUBN: {
        std::shared_ptr<TupleValue> lvalue, rvalue;
        rc = Calculate(lvalue, tuple, field_index, a->l);
        if (rc != RC::SUCCESS) {
            return rc;
        }
        rc = Calculate(rvalue, tuple, field_index, a->r);
        if (rc != RC::SUCCESS) {
            return rc;
        }
        value = std::shared_ptr<TupleValue>(new FloatValue(lvalue->value() - rvalue->value()));
    } break;
    case NodeType::MULN: {
        std::shared_ptr<TupleValue> lvalue, rvalue;
        rc = Calculate(lvalue, tuple, field_index, a->l);
        if (rc != RC::SUCCESS) {
            return rc;
        }
        rc = Calculate(rvalue, tuple, field_index, a->r);
        if (rc != RC::SUCCESS) {
            return rc;
        }
        value = std::shared_ptr<TupleValue>(new FloatValue(lvalue->value() * rvalue->value()));
    } break;
    case NodeType::DIVN: {
        // todo(wq): exp 除0 错误 可以用null返回
        std::shared_ptr<TupleValue> lvalue, rvalue;
        rc = Calculate(lvalue, tuple, field_index, a->l);
        if (rc != RC::SUCCESS) {
            return rc;
        }
        rc = Calculate(rvalue, tuple, field_index, a->r);
        if (rc != RC::SUCCESS) {
            return rc;
        }
        if (rvalue->value() == 0) {
            return RC::GENERIC_ERROR;
        }
        value = std::shared_ptr<TupleValue>(new FloatValue(lvalue->value() / rvalue->value()));
    } break;
    case NodeType::VALN: {
        Value &val = ((valnode *)a)->value;
        assert(val.type == AttrType::INTS || val.type == AttrType::FLOATS);
        if (val.type == AttrType::INTS) {
            value = std::shared_ptr<TupleValue>(new FloatValue(*((int *)(val.data))));
        } else if (val.type == AttrType::FLOATS) {
            value = std::shared_ptr<TupleValue>(new FloatValue(*((float *)(val.data))));
        }
    } break;
    case NodeType::ATTRN: {
        RelAttr &attr = ((attrnode *)a)->attr;
        std::string table_name;
        if (field_index.size() == 1) {
            table_name = field_index.begin()->first;
        } else {
            table_name = attr.relation_name;
        }
        value = tuple.get_pointer(field_index.at(table_name).at(attr.attribute_name));
        assert(value->Type() == AttrType::INTS || value->Type() == AttrType::FLOATS);
    } break;
    default:
        assert(false);
        break;
    }
    return rc;
}

RC AstUtil::PrintNodeType(std::string &str, NodeType node_type) {
    switch (node_type) {
    case NodeType::ADDN: {
        str.push_back('+');
    } break;
    case NodeType::SUBN: {
        str.push_back('-');
    } break;
    case NodeType::MULN: {
        str.push_back('*');
    } break;
    case NodeType::DIVN: {
        str.push_back('/');
    } break;
    default:
        assert(false);
    }
    return RC::SUCCESS;
}

RC AstUtil::PrintValue(std::string &str, Value &value) {
    std::stringstream ss;
    switch (value.type) {
    case AttrType::INTS: {
        IntValue(*((int *)value.data)).to_string(ss);
    } break;
    case AttrType::FLOATS: {
        FloatValue(*((float *)value.data)).to_string(ss);
    } break;
    case AttrType::CHARS: {
        StringValue((char *)value.data).to_string(ss);
    } break;
    default:
        assert(false);
    }
    str += ss.str();
    return RC::SUCCESS;
}

RC AstUtil::Print(std::string &str, ast *a) {
    RC rc = RC::SUCCESS;
    for (int i = 0; i < a->l_brace; i++) {
        str.push_back('(');
    }
    switch (a->nodetype) {
    case NodeType::ADDN:;
    case NodeType::SUBN:;
    case NodeType::MULN:;
    case NodeType::DIVN: {
        if (a->l != nullptr) {
            rc = Print(str, a->l);
            assert(rc == RC::SUCCESS);
        }
        rc = PrintNodeType(str, a->nodetype);
        assert(rc == RC::SUCCESS);
        rc = Print(str, a->r);
        assert(rc == RC::SUCCESS);
    } break;
    case NodeType::VALN: {
        rc = PrintValue(str, ((valnode *)a)->value);
        assert(rc == RC::SUCCESS);
    } break;
    case NodeType::ATTRN: {
        RelAttr &attr = ((attrnode *)a)->attr;
        if (attr.relation_name != nullptr) {
            str += std::string(attr.relation_name) + '.';
        }
        str += attr.attribute_name;
    } break;
    default:
    assert(false);
    }
    for (int i = 0; i < a->r_brace; i++) {
        str += ')';
    }
    return RC::SUCCESS;
}
