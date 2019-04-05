#include "binary-operator.hpp"

namespace Irt {

BinaryOperator::BinaryOperator(ArithmeticOperator arithmeticOperator,
                               std::shared_ptr<Expression> leftExpression,
                               std::shared_ptr<Expression> rightExpression)
    : arithmeticOperator_{arithmeticOperator},
      leftExpression_{leftExpression},
      rightExpression_{rightExpression} {
  assert(leftExpression_ != nullptr);
  assert(rightExpression_ != nullptr);
}

void BinaryOperator::Accept(Visitor* visitor) { visitor->Visit(this); }

}  // namespace Irt
