#pragma once

#include <memory>
#include <string>
#include "expression.hpp"
#include "statement.hpp"

namespace Ast {

class AssignmentStatement : public Statement {
 public:
  AssignmentStatement(Location location, const std::string& variable,
                      std::unique_ptr<Expression> expression);

  void Accept(Visitor* visitor) final;

 public:
  const std::string variable_;
  const std::unique_ptr<Expression> expression_;
};

inline AssignmentStatement::AssignmentStatement(
    Location location, const std::string& variable,
    std::unique_ptr<Expression> expression)
    : variable_{variable}, expression_{std::move(expression)} {
  SetLocation(location);
  assert(expression_ != nullptr);
}

inline void AssignmentStatement::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

}  // namespace Ast
