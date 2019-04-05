#pragma once

#include <memory>
#include "expression.hpp"

namespace Ct {

class Statement;

class ExpressionSequence : public Expression {
 public:
  ExpressionSequence(std::shared_ptr<Statement> statement,
                     std::shared_ptr<Expression> expression);

  void Accept(Visitor* visitor) final;

  std::vector<std::shared_ptr<Expression>> Kids() final;

  std::shared_ptr<Expression> Build(
      const std::vector<std::shared_ptr<Expression>>& expressionList) final;

 public:
  const std::shared_ptr<Statement> statement_;
  const std::shared_ptr<Expression> expression_;
};

inline ExpressionSequence::ExpressionSequence(
    std::shared_ptr<Statement> statement,
    std::shared_ptr<Expression> expression)
    : statement_{std::move(statement)}, expression_{std::move(expression)} {
  assert(statement_ != nullptr);
  assert(expression_ != nullptr);
}

inline void ExpressionSequence::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

inline std::vector<std::shared_ptr<Expression>> ExpressionSequence::Kids() {
  return {expression_};
}

inline std::shared_ptr<Expression> ExpressionSequence::Build(
    const std::vector<std::shared_ptr<Expression>>& expressionList) {
  return std::make_shared<ExpressionSequence>(statement_, expressionList[0]);
}

}  // namespace Ct
