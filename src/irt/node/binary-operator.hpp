#pragma once

#include <memory>
#include "expression.hpp"

namespace Irt {

enum class ArithmeticOperator { Plus, Minus, Multiplication };

class BinaryOperator : public Expression {
 public:
  BinaryOperator(ArithmeticOperator arithmeticOperator,
                 std::shared_ptr<Expression> leftExpression,
                 std::shared_ptr<Expression> rightExpression);

  void Accept(Visitor *visitor) final;

 public:
  const ArithmeticOperator arithmeticOperator_;
  const std::shared_ptr<Expression> leftExpression_;
  const std::shared_ptr<Expression> rightExpression_;
};

inline BinaryOperator::BinaryOperator(
    ArithmeticOperator arithmeticOperator,
    std::shared_ptr<Expression> leftExpression,
    std::shared_ptr<Expression> rightExpression)
    : arithmeticOperator_{arithmeticOperator},
      leftExpression_{std::move(leftExpression)},
      rightExpression_{std::move(rightExpression)} {
  assert(leftExpression_ != nullptr);
  assert(rightExpression_ != nullptr);
}

inline void BinaryOperator::Accept(Visitor *visitor) { visitor->Visit(this); }

}  // namespace Irt
