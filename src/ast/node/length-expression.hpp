#pragma once

#include <memory>
#include "expression.hpp"

namespace Ast {

class LengthExpression : public Expression {
 public:
  explicit LengthExpression(Location location,
                            std::unique_ptr<Expression> expression);

  void Accept(Visitor* visitor) final;

 public:
  const std::unique_ptr<Expression> expression_;
};

inline LengthExpression::LengthExpression(
    Location location, std::unique_ptr<Expression> expression)
    : expression_{std::move(expression)} {
  SetLocation(location);
  assert(expression_ != nullptr);
}

inline void LengthExpression::Accept(Visitor* visitor) { visitor->Visit(this); }

}  // namespace Ast
