#pragma once

#include <memory>
#include <vector>
#include "expression.hpp"
#include "node.hpp"
#include "statement.hpp"
#include "var-declaration.hpp"

namespace Ast {

class MethodBody : public Node {
 public:
  MethodBody(Location location,
             std::vector<std::unique_ptr<VarDeclaration>>& variables,
             std::vector<std::unique_ptr<Statement>>& statements,
             std::unique_ptr<Expression> returnExpression);

  void Accept(Visitor* visitor) final;

 public:
  const std::vector<std::unique_ptr<VarDeclaration>> variables_;
  const std::vector<std::unique_ptr<Statement>> statements_;
  const std::unique_ptr<Expression> returnExpression_;
};

inline MethodBody::MethodBody(
    Location location, std::vector<std::unique_ptr<VarDeclaration>>& variables,
    std::vector<std::unique_ptr<Statement>>& statements,
    std::unique_ptr<Expression> returnExpression)
    : variables_{std::move(variables)},
      statements_{std::move(statements)},
      returnExpression_{std::move(returnExpression)} {
  SetLocation(location);
  assert(returnExpression_ != nullptr);
}

inline void MethodBody::Accept(Visitor* visitor) { visitor->Visit(this); }

}  // namespace Ast
