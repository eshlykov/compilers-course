#pragma once

#include <memory>
#include <vector>

#include <ast/node/visitor-target.hpp>
#include <ast/visitor/visitor.hpp>

#include <ast/node/method-declaration.hpp>

namespace Ast {

class MethodDeclarationList : public VisitorTarget {
 public:
  MethodDeclarationList(const Location& location) : VisitorTarget(location) {}

  void Add(const MethodDeclaration* declaration) {
    declarations_.emplace_back(declaration);
  }

  const std::vector<std::unique_ptr<const MethodDeclaration> >&
  MethodDeclarations() const {
    return declarations_;
  }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  std::vector<std::unique_ptr<const MethodDeclaration> > declarations_;
};

}  // namespace Ast
