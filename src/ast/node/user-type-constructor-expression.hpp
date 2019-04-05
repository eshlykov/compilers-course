#pragma once

#include <string>
#include "expression.hpp"

namespace Ast {

class UserTypeConstructorExpression : public Expression {
 public:
  explicit UserTypeConstructorExpression(Location location,
                                         const std::string& name);

  void Accept(Visitor* visitor) final;

 public:
  const std::string name_;
};

inline UserTypeConstructorExpression::UserTypeConstructorExpression(
    Location location, const std::string& name)
    : name_{name} {
  SetLocation(location);
}

inline void UserTypeConstructorExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

}  // namespace Ast
