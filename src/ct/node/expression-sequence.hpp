#pragma once

#include <memory>
#include "expression.hpp"

namespace Ct {

class Statement;

class ExpressionSequence : public Expression {
 public:
  ExpressionSequence(StatementPtr statement, ExpressionPtr expression);

  void Accept(Visitor* visitor) final;

  std::vector<ExpressionPtr> Kids() final;

  ExpressionPtr Build(const std::vector<ExpressionPtr>& expressionList) final;

 public:
  const StatementPtr statement_;
  const ExpressionPtr expression_;
};

inline ExpressionSequence::ExpressionSequence(StatementPtr statement,
                                              ExpressionPtr expression)
    : statement_{std::move(statement)}, expression_{std::move(expression)} {
  assert(statement_ != nullptr);
  assert(expression_ != nullptr);
}

inline void ExpressionSequence::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

inline std::vector<ExpressionPtr> ExpressionSequence::Kids() {
  return {expression_};
}

inline ExpressionPtr ExpressionSequence::Build(
    const std::vector<ExpressionPtr>& expressionList) {
  return std::make_shared<ExpressionSequence>(statement_, expressionList[0]);
}

using ExpressionSequencePtr = std::shared_ptr<ExpressionSequence>;

}  // namespace Ct
