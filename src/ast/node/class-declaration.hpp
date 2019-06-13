#pragma once

#include <memory>

#include <ast/node/visitor-target.hpp>
#include <ast/visitor/visitor.hpp>

#include <ast/node/expression.hpp>
#include <ast/node/method-declaration-list.hpp>
#include <ast/node/var-declaration-list.hpp>

namespace Ast {

class ClassDeclaration : public VisitorTarget {
 public:
  ClassDeclaration(const IdExpression* className,
                   const VarDeclarationList* varDelcs,
                   const MethodDeclarationList* methodDecls,
                   const Location& location)
      : VisitorTarget(location),
        className_(className),
        varDecls_(varDelcs),
        methodDecls_(methodDecls),
        hasParent_(false) {}

  ClassDeclaration(const IdExpression* className,
                   const VarDeclarationList* varDecls,
                   const MethodDeclarationList* methodDecls,
                   const IdExpression* parent, const Location& location)
      : VisitorTarget(location),
        className_(className),
        varDecls_(varDecls),
        methodDecls_(methodDecls),
        hasParent_(true),
        extendsClassName_(parent) {}

  const IdExpression* ClassName() const { return className_.get(); }
  const VarDeclarationList* VarDeclarations() const { return varDecls_.get(); }
  const MethodDeclarationList* MethodDeclarations() const {
    return methodDecls_.get();
  }
  bool HasParent() const { return hasParent_; }
  const IdExpression* ExtendsClassName() const {
    return extendsClassName_.get();
  }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  std::unique_ptr<const IdExpression> className_;
  std::unique_ptr<const VarDeclarationList> varDecls_;
  std::unique_ptr<const MethodDeclarationList> methodDecls_;
  bool hasParent_;
  std::unique_ptr<const IdExpression> extendsClassName_;
};

}  // namespace Ast
