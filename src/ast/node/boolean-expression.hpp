#pragma once

#include "expression.hpp"

namespace Ast {

class BooleanExpression : public Expression {
 public:
  explicit BooleanExpression(Location location, bool value);

  void Accept(Visitor *visitor) final;

 public:
  const bool value_;
};

inline BooleanExpression::BooleanExpression(Location location, bool value)
    : value_{value} {
  SetLocation(location);
}

inline void BooleanExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}

}  // namespace Ast
