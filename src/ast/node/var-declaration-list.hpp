#pragma once

#include <memory>
#include <vector>

#include <ast/node/visitor-target.hpp>
#include <ast/visitor/visitor.hpp>

#include <ast/node/expression.hpp>
#include <ast/node/type-modifier.hpp>
#include <ast/node/var-declaration.hpp>

namespace Ast {

class VarDeclarationList : public VisitorTarget {
 public:
  VarDeclarationList(const Location& location) : VisitorTarget(location) {}

  void Add(const VarDeclaration* varDeclaration) {
    varDeclarations_.emplace_back(varDeclaration);
  }

  const std::vector<std::unique_ptr<const VarDeclaration> >& VarDeclarations()
      const {
    return varDeclarations_;
  }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  std::vector<std::unique_ptr<const VarDeclaration> > varDeclarations_;
};

}  // namespace Ast
