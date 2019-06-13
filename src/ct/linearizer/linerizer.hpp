#pragma once

#include <algorithm>
#include <memory>
#include <vector>
#include "../../utils/ct.hpp"
#include "expression-call.hpp"
#include "move-call.hpp"
#include "statement-expression-list.hpp"

#include "../../parser.hpp"

namespace Ct {

class Linearizer {
 public:
  std::vector<StatementPtr> Linearize(const StatementPtr& statement);

 private:
  static bool IsNop(const StatementPtr& statement);

  static StatementPtr Sequence(StatementPtr first, StatementPtr second);

  static bool Commute(const StatementPtr& first, const ExpressionPtr& second);

  StatementPtr DoStatement(const StatementSequencePtr& statement);

  StatementPtr DoStatement(const MovePtr& moveStatement);

  StatementPtr DoStatement(const VoidPtr& voidStatement);

  StatementPtr DoStatement(const StatementPtr& statement);

  StatementPtr ReorderStatement(const StatementPtr& statement);

  ExpressionSequencePtr DoExpression(
      const ExpressionSequencePtr& expressionSequence);

  ExpressionSequencePtr DoExpression(const ExpressionPtr& expression);

  ExpressionSequencePtr ReorderExpression(const ExpressionPtr& expression);

  std::shared_ptr<StatementExpressionList> Reorder(
      const std::vector<ExpressionPtr>& list);

  std::vector<StatementPtr> Linearize(const StatementSequencePtr& statement,
                                      const std::vector<StatementPtr>& list);

  std::vector<StatementPtr> Linearize(const StatementPtr& statement,
                                      const std::vector<StatementPtr>& list);

 private:
  const std::shared_ptr<StatementExpressionList> NopNull =
      std::make_shared<StatementExpressionList>(
          std::make_shared<Void>(std::make_shared<Constant>(0)),
          std::vector<ExpressionPtr>());
};

}  // namespace Ct
