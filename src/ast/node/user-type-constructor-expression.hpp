#pragma once

#include <string>
#include "expression.hpp"

namespace Ast {

class UserTypeConstructorExpression : public Expression {
 public:
  explicit UserTypeConstructorExpression(Location location, std::string name);

  void Accept(Visitor* visitor) final;

 public:
  const std::string name_;
};

inline UserTypeConstructorExpression::UserTypeConstructorExpression(
    Location location, std::string name)
    : name_{std::move(name)} {
  SetLocation(location);
}

inline void UserTypeConstructorExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

}  // namespace Ast
