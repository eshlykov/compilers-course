#pragma once

#include <memory>
#include "statement.hpp"

namespace Ct {

class Expression;

class Void : public Statement {
 public:
  explicit Void(ExpressionPtr expression);

  void Accept(Visitor* visitor) final;

  std::vector<ExpressionPtr> Kids() final;

  StatementPtr Build(const std::vector<ExpressionPtr>& expressionList) final;

 public:
  const ExpressionPtr expression_;
};

inline Void::Void(ExpressionPtr expression)
    : expression_{std::move(expression)} {
  assert(expression_ != nullptr);
}

inline void Void::Accept(Visitor* visitor) { visitor->Visit(this); }

inline std::vector<ExpressionPtr> Void::Kids() { return {expression_}; }

inline StatementPtr Void::Build(
    const std::vector<ExpressionPtr>& expressionList) {
  return std::make_shared<Void>(expressionList[0]);
}

using VoidPtr = std::shared_ptr<Void>;

}  // namespace Ct
