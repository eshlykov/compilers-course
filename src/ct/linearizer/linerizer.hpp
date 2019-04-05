#pragma once

#include <algorithm>
#include <memory>
#include <vector>
#include "../../utils/ct.hpp"
#include "expression-call.hpp"
#include "move-call.hpp"
#include "statement-expression-list.hpp"

namespace Ct {

class Linearizer : public Visitor {
 public:
  std::vector<std::shared_ptr<Statement>> Linearize(
      const std::shared_ptr<Statement>& statement);

 private:
  static bool IsNop(const std::shared_ptr<Statement>& statement);

  static std::shared_ptr<Statement> Sequence(std::shared_ptr<Statement> first,
                                             std::shared_ptr<Statement> second);

  static bool Commute(const std::shared_ptr<Statement>& first,
                      const std::shared_ptr<Expression>& second);

  std::shared_ptr<Statement> DoStatement(
      const std::shared_ptr<StatementSequence>& statement);

  std::shared_ptr<Statement> DoStatement(
      const std::shared_ptr<Move>& moveStatement);

  std::shared_ptr<Statement> DoStatement(
      const std::shared_ptr<Void>& voidStatement);

  std::shared_ptr<Statement> DoStatement(
      const std::shared_ptr<Statement>& statement);

  std::shared_ptr<Statement> ReorderStatement(
      const std::shared_ptr<Statement>& statement);

  std::shared_ptr<ExpressionSequence> DoExpression(
      const std::shared_ptr<ExpressionSequence>& expressionSequence);

  std::shared_ptr<ExpressionSequence> DoExpression(
      const std::shared_ptr<Expression>& expression);

  std::shared_ptr<ExpressionSequence> ReorderExpression(
      const std::shared_ptr<Expression>& expression);

  std::shared_ptr<StatementExpressionList> Reorder(
      const std::vector<std::shared_ptr<Expression>>& list);

  std::vector<std::shared_ptr<Statement>> Linearize(
      const std::shared_ptr<StatementSequence>& statement,
      const std::vector<std::shared_ptr<Statement>>& list);

  std::vector<std::shared_ptr<Statement>> Linearize(
      const std::shared_ptr<Statement>& statement,
      const std::vector<std::shared_ptr<Statement>>& list);

 private:
  const std::shared_ptr<StatementExpressionList> NopNull =
      std::make_shared<StatementExpressionList>(
          std::make_shared<Void>(std::make_shared<Constant>(0)),
          std::vector<std::shared_ptr<Expression>>());
};

}  // namespace Ct
