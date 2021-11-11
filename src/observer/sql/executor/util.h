#include <map>
#include <string>
#include "sql/executor/tuple.h"
#include "storage/common/table.h"

class TupleSortUtil {
public:
  static bool cmp(const Tuple &lhs, const Tuple &rhs) {
    int ret = 0;
    for (const TupleField &field : order_by_schema_->fields()) {
      // const map无法用下标取值
      int index = field_index_->at(field.table_name()).at(field.field_name());
      ret = lhs.get_pointer(index)->compare(*(rhs.get_pointer(index)));
      if (ret != 0) {
        if (field.order() == 0) {
          // ASC
          return ret < 0;
        } else {
          // DESC
          return ret > 0;
        }
      }
    }
    return ret < 0;
  }

  static void set(const std::map<std::string, std::map<std::string, int>> &field_index, const TupleSchema &order_by_schema) {
    field_index_ = &field_index;
    order_by_schema_ = &order_by_schema;
  }
private:
  // {table_name: {field_name, index}}
  static const std::map<std::string, std::map<std::string, int>> *field_index_;
  static const TupleSchema *order_by_schema_;
};
