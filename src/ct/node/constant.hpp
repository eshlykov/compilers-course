#pragma once

#include "expression.hpp"

namespace Ct {

class Constant : public Expression {
 public:
  explicit Constant(int value);

  virtual void Accept(Visitor* visitor) override final;

  virtual std::vector<std::shared_ptr<Expression>> Kids() override final;

  virtual std::shared_ptr<Expression> Build(
      const std::vector<std::shared_ptr<Expression>>& expressionList)
      override final;

 public:
  const int value_;
};

inline Constant::Constant(int value) : value_{value} {}

inline void Constant::Accept(Visitor* visitor) { visitor->Visit(this); }

inline std::vector<std::shared_ptr<Expression>> Constant::Kids() { return {}; }

inline std::shared_ptr<Expression> Constant::Build(
    const std::vector<std::shared_ptr<Expression>>& expressionList) {
  return std::make_shared<Constant>(value_);
}

}  // namespace Ct
