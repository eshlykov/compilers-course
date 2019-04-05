#pragma once

#include "expression.hpp"

namespace Ct {

class Constant : public Expression {
 public:
  explicit Constant(int value);

  void Accept(Visitor* visitor) final;

  std::vector<ExpressionPtr> Kids() final;

  ExpressionPtr Build(const std::vector<ExpressionPtr>& expressionList) final;

 public:
  const int value_;
};

inline Constant::Constant(int value) : value_{value} {}

inline void Constant::Accept(Visitor* visitor) { visitor->Visit(this); }

inline std::vector<ExpressionPtr> Constant::Kids() { return {}; }

inline ExpressionPtr Constant::Build(
    const std::vector<ExpressionPtr>& expressionList) {
  return std::make_shared<Constant>(value_);
}

using ConstantPtr = std::shared_ptr<Constant>;

}  // namespace Ct
