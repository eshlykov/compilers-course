#pragma once

#include <memory>
#include "expression.hpp"

namespace Irt {

class Statement;

class ExpressionSequence : public Expression {
 public:
  ExpressionSequence(std::shared_ptr<Statement> statement,
                     std::shared_ptr<Expression> expression);

  void Accept(Visitor* visitor) final;

 public:
  const std::shared_ptr<Statement> statement_;
  const std::shared_ptr<Expression> expression_;
};

inline ExpressionSequence::ExpressionSequence(
    std::shared_ptr<Statement> statement,
    std::shared_ptr<Expression> expression)
    : statement_{statement}, expression_{expression} {
  assert(statement_ != nullptr);
  assert(expression_ != nullptr);
}

inline void ExpressionSequence::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

}  // namespace Irt
