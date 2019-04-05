#pragma once

#include <memory>
#include "expression.hpp"

namespace Ct {

class Memory : public Expression {
 public:
  explicit Memory(ExpressionPtr expression);

  void Accept(Visitor* visitor) final;

  std::vector<ExpressionPtr> Kids() final;

  ExpressionPtr Build(const std::vector<ExpressionPtr>& expressionList) final;

 public:
  const ExpressionPtr expression_;
};

inline Memory::Memory(ExpressionPtr expression)
    : expression_{std::move(expression)} {
  assert(expression_ != nullptr);
}

inline void Memory::Accept(Visitor* visitor) { visitor->Visit(this); }

inline std::vector<ExpressionPtr> Memory::Kids() { return {expression_}; }

inline ExpressionPtr Memory::Build(
    const std::vector<ExpressionPtr>& expressionList) {
  return std::make_shared<Memory>(expressionList[0]);
}

using MemoryPtr = std::shared_ptr<Memory>;

}  // namespace Ct
