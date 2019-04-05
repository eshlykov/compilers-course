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

  virtual void Accept(Visitor* visitor) override final;

 public:
  const ArithmeticOperator arithmeticOperator_;
  const std::shared_ptr<Expression> leftExpression_;
  const std::shared_ptr<Expression> rightExpression_;
};

}  // namespace Irt
