#pragma once

#include <memory>
#include "statement.hpp"

namespace Ct {

class Expression;

class Void : public Statement {
 public:
  explicit Void(std::shared_ptr<Expression> expression);

  void Accept(Visitor* visitor) final;

  std::vector<std::shared_ptr<Expression>> Kids() final;

  std::shared_ptr<Statement> Build(
      const std::vector<std::shared_ptr<Expression>>& expressionList) final;

 public:
  const std::shared_ptr<Expression> expression_;
};

inline Void::Void(std::shared_ptr<Expression> expression)
    : expression_{expression} {
  assert(expression_ != nullptr);
}

inline void Void::Accept(Visitor* visitor) { visitor->Visit(this); }

inline std::vector<std::shared_ptr<Expression>> Void::Kids() {
  return {expression_};
}

inline std::shared_ptr<Statement> Void::Build(
    const std::vector<std::shared_ptr<Expression>>& expressionList) {
  return std::make_shared<Void>(expressionList[0]);
}

}  // namespace Ct
