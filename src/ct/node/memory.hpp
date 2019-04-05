#pragma once

#include <memory>
#include "expression.hpp"

namespace Ct {

class Memory : public Expression {
 public:
  explicit Memory(std::shared_ptr<Expression> expression);

  virtual void Accept(Visitor* visitor) override final;

  virtual std::vector<std::shared_ptr<Expression>> Kids() override final;

  virtual std::shared_ptr<Expression> Build(
      const std::vector<std::shared_ptr<Expression>>& expressionList)
      override final;

 public:
  const std::shared_ptr<Expression> expression_;
};

inline Memory::Memory(std::shared_ptr<Expression> expression)
    : expression_{expression} {
  assert(expression_ != nullptr);
}

inline void Memory::Accept(Visitor* visitor) { visitor->Visit(this); }

inline std::vector<std::shared_ptr<Expression>> Memory::Kids() {
  return {expression_};
}

inline std::shared_ptr<Expression> Memory::Build(
    const std::vector<std::shared_ptr<Expression>>& expressionList) {
  return std::make_shared<Memory>(expressionList[0]);
}

}  // namespace Ct
