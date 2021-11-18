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

class AstUtil {
public:
	/**
	 * value: 返回值
	 * tuple: 需要求值的tuple
	 * tuple_schema: tuple对应的schema
	 * 用来求对应tuple通过expression_ast产生的值，如果计算出错，则返回NullValue
	 */
  static RC Calculate(std::shared_ptr<TupleValue> &value, const Tuple &tuple, const std::map<std::string, std::map<std::string, int>> &field_index, ast *a);


  static RC PrintNodeType(std::string &str, NodeType node_type);
  static RC PrintValue(std::string &str, Value &value);
  static RC Print(std::string &str, ast *a);
};
