#pragma once

#include <memory>
#include <vector>
#include "method-declaration.hpp"
#include "node.hpp"
#include "var-declaration.hpp"

namespace Ast {

class ClassBody : public Node {
 public:
  ClassBody(Location location,
            std::vector<std::unique_ptr<VarDeclaration>>& variables,
            std::vector<std::unique_ptr<MethodDeclaration>>& methods);

  void Accept(Visitor* visitor) final;

 public:
  const std::vector<std::unique_ptr<VarDeclaration>> variables_;
  const std::vector<std::unique_ptr<MethodDeclaration>> methods_;
};

inline ClassBody::ClassBody(
    Location location, std::vector<std::unique_ptr<VarDeclaration>>& variables,
    std::vector<std::unique_ptr<MethodDeclaration>>& methods)
    : variables_{std::move(variables)}, methods_{std::move(methods)} {
  SetLocation(location);
}

inline void ClassBody::Accept(Visitor* visitor) { visitor->Visit(this); }

}  // namespace Ast
