#include "sql/executor/tuple.h"
#include "storage/common/table.h"

class TupleSortUtil {
public:
  static bool cmp(const Tuple &lhs, const Tuple &rhs) {
    int ret = 0;
    for (const TupleField &field : order_by_schema_->fields()) {
      // 减去sys_field的偏移
      int index = table_->table_meta().field_index(field.field_name()) - table_->table_meta().sys_field_num();
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

  static void set(const Table &table, const TupleSchema &order_by_schema) {
    table_ = &table;
    order_by_schema_ = &order_by_schema;
  }
private:
  static const Table *table_;
  static const TupleSchema *order_by_schema_;
};

const Table *TupleSortUtil::table_ = nullptr;
const TupleSchema *TupleSortUtil::order_by_schema_ = nullptr;

