#pragma once

#include <memory>
#include <vector>

#include <ast/node/visitor-target.hpp>
#include <ast/visitor/visitor.hpp>

#include <ast/node/class-declaration.hpp>

namespace Ast {

class ClassDeclarationList : public VisitorTarget {
 public:
  ClassDeclarationList(const Location& location) : VisitorTarget(location) {}

  void Add(const ClassDeclaration* declaration) {
    classes_.emplace_back(declaration);
  }

  const std::vector<std::unique_ptr<const ClassDeclaration>>&
  ClassDeclarations() const {
    return classes_;
  }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  std::vector<std::unique_ptr<const ClassDeclaration>> classes_;
};

}  // namespace Ast
