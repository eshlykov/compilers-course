#pragma once

#include <memory>
#include "expression.hpp"

namespace Ast {

enum class BinaryOperator {
  And,
  Less,
  Plus,
  Minus,
  Star,
};

class BinaryOperatorExpression : public Expression {
 public:
  BinaryOperatorExpression(Location location, std::unique_ptr<Expression> lhs,
                           std::unique_ptr<Expression> rhs,
                           BinaryOperator binaryOperator);

  void Accept(Visitor *visitor) final;

 public:
  const std::unique_ptr<Expression> lhs_;
  const std::unique_ptr<Expression> rhs_;
  const BinaryOperator binaryOperator_;
};

inline BinaryOperatorExpression::BinaryOperatorExpression(
    Location location, std::unique_ptr<Expression> lhs,
    std::unique_ptr<Expression> rhs, BinaryOperator binaryOperator)
    : lhs_{std::move(lhs)},
      rhs_{std::move(rhs)},
      binaryOperator_{binaryOperator} {
  SetLocation(location);
  assert(lhs_ != nullptr);
  assert(rhs_ != nullptr);
}

inline void BinaryOperatorExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}

}  // namespace Ast
