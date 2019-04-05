#pragma once

#include "expression.hpp"

namespace Ct {

class Constant : public Expression {
 public:
  explicit Constant(int value);

  void Accept(Visitor *visitor) final;

  std::vector<std::shared_ptr<Expression>> Kids() final;

  std::shared_ptr<Expression> Build(
      const std::vector<std::shared_ptr<Expression>> &expressionList) final;

 public:
  const int value_;
};

inline Constant::Constant(int value) : value_{value} {}

inline void Constant::Accept(Visitor *visitor) { visitor->Visit(this); }

inline std::vector<std::shared_ptr<Expression>> Constant::Kids() { return {}; }

inline std::shared_ptr<Expression> Constant::Build(
    const std::vector<std::shared_ptr<Expression>> &expressionList) {
  return std::make_shared<Constant>(value_);
}

}  // namespace Ct
