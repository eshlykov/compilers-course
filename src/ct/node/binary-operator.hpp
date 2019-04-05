#pragma once

#include <memory>
#include "expression.hpp"

namespace Ct {

enum class ArithmeticOperator { Plus, Minus, Multiplication };

class BinaryOperator : public Expression {
 public:
  BinaryOperator(ArithmeticOperator arithmeticOperator,
                 std::shared_ptr<Expression> leftExpression,
                 std::shared_ptr<Expression> rightExpression);

  void Accept(Visitor *visitor) final;

  std::vector<std::shared_ptr<Expression>> Kids() final;

  std::shared_ptr<Expression> Build(
      const std::vector<std::shared_ptr<Expression>> &expressionList) final;

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

inline std::vector<std::shared_ptr<Expression>> BinaryOperator::Kids() {
  return {leftExpression_, rightExpression_};
}

inline std::shared_ptr<Expression> BinaryOperator::Build(
    const std::vector<std::shared_ptr<Expression>> &expressionList) {
  return std::make_shared<BinaryOperator>(arithmeticOperator_,
                                          expressionList[0], expressionList[1]);
}

}  // namespace Ct
