#pragma once

#include <memory>
#include "expression.hpp"

namespace Ast {

class IntArrayConstructorExpression : public Expression {
 public:
  explicit IntArrayConstructorExpression(
      Location location, std::unique_ptr<Expression> expression);

  void Accept(Visitor* visitor) final;

 public:
  const std::unique_ptr<Expression> expression_;
};

inline IntArrayConstructorExpression::IntArrayConstructorExpression(
    Location location, std::unique_ptr<Expression> expression)
    : expression_{std::move(expression)} {
  SetLocation(location);
  assert(expression_ != nullptr);
}

inline void IntArrayConstructorExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

}  // namespace Ast
