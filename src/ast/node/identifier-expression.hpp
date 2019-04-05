#pragma once

#include <string>
#include "expression.hpp"

namespace Ast {

class IdentifierExpression : public Expression {
 public:
  IdentifierExpression(Location location, const std::string& name);

  void Accept(Visitor* visitor) final;

 public:
  const std::string name_;
};

inline IdentifierExpression::IdentifierExpression(Location location,
                                                  const std::string& name)
    : name_{name} {
  SetLocation(location);
}

inline void IdentifierExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

}  // namespace Ast
