#pragma once

#include <memory>
#include "expression.hpp"

namespace Ct {

enum class ArithmeticOperator { Plus, Minus, Multiplication };

class BinaryOperator : public Expression {
 public:
  BinaryOperator(ArithmeticOperator arithmeticOperator,
                 ExpressionPtr leftExpression, ExpressionPtr rightExpression);

  void Accept(Visitor* visitor) final;

  std::vector<ExpressionPtr> Kids() final;

  ExpressionPtr Build(const std::vector<ExpressionPtr>& expressionList) final;

 public:
  const ArithmeticOperator arithmeticOperator_;
  const ExpressionPtr leftExpression_;
  const ExpressionPtr rightExpression_;
};

inline BinaryOperator::BinaryOperator(ArithmeticOperator arithmeticOperator,
                                      ExpressionPtr leftExpression,
                                      ExpressionPtr rightExpression)
    : arithmeticOperator_{arithmeticOperator},
      leftExpression_{std::move(leftExpression)},
      rightExpression_{std::move(rightExpression)} {
  assert(leftExpression_ != nullptr);
  assert(rightExpression_ != nullptr);
}

inline void BinaryOperator::Accept(Visitor* visitor) { visitor->Visit(this); }

inline std::vector<ExpressionPtr> BinaryOperator::Kids() {
  return {leftExpression_, rightExpression_};
}

inline ExpressionPtr BinaryOperator::Build(
    const std::vector<ExpressionPtr>& expressionList) {
  return std::make_shared<BinaryOperator>(arithmeticOperator_,
                                          expressionList[0], expressionList[1]);
}

using BinaryOperatorPtr = std::shared_ptr<BinaryOperator>;

}  // namespace Ct
