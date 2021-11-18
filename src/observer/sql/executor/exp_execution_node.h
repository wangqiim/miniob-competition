#include "storage/common/condition_filter.h"
#include "sql/executor/tuple.h"
#include "sql/executor/execution_node.h"
#include <memory>

class ExpExeNode: public ExecutionNode {
public:
  ExpExeNode() = default;
  ~ExpExeNode() { delete condition_filter_; }

  RC init(TupleSchema &&output_tuple_schema, TupleSet &&tuple_set, CompositeExpressionFilter *condition_filter,
          const std::map<std::string, std::map<std::string, int>> &field_index);

  RC execute(TupleSet &output_tuple_set) override;
private:
  TupleSchema output_tuple_schema_; // output schema
  CompositeExpressionFilter *condition_filter_; // expression filter
  TupleSet tuple_set_;
  const std::map<std::string, std::map<std::string, int>> *field_index_;
};

RC create_expression_executor(const Selects &selects, ExpExeNode &exp_exe_node, TupleSet &&tuple_set, TupleSchema &output_schema, const std::map<std::string, std::map<std::string, int>> &field_index);
