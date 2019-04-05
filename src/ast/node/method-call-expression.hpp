#pragma once

#include <memory>
#include <string>
#include <vector>
#include "expression.hpp"

namespace Ast {

class MethodCallExpression : public Expression {
 public:
  MethodCallExpression(Location location,
                       std::unique_ptr<Expression> expression,
                       const std::string& methodName,
                       std::vector<std::unique_ptr<Expression>>& argumentsList);

  void Accept(Visitor* visitor) final;

 public:
  const std::unique_ptr<Expression> expression_;
  const std::string methodName_;
  const std::vector<std::unique_ptr<Expression>> argumentsList_;
};

inline MethodCallExpression::MethodCallExpression(
    Location location, std::unique_ptr<Expression> expression,
    const std::string& methodName,
    std::vector<std::unique_ptr<Expression>>& argumentsList)
    : expression_{std::move(expression)},
      methodName_{methodName},
      argumentsList_{std::move(argumentsList)} {
  SetLocation(location);
  assert(expression_ != nullptr);
}

inline void MethodCallExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

}  // namespace Ast
