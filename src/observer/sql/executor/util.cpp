#include <sql/executor/util.h>

const std::map<std::string, std::map<std::string, int>> *TupleSortUtil::field_index_ = nullptr;
const TupleSchema *TupleSortUtil::order_by_schema_ = nullptr;