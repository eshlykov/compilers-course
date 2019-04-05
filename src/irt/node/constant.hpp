#pragma once

#include "expression.hpp"

namespace Irt {

class Constant : public Expression {
 public:
  explicit Constant(int value);

  void Accept(Visitor* visitor) final;

 public:
  const int value_;
};

inline Constant::Constant(int value) : value_{value} {}

inline void Constant::Accept(Visitor* visitor) { visitor->Visit(this); }

}  // namespace Irt
