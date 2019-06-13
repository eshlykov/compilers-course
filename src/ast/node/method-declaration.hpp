#pragma once

#include <memory>

#include <ast/node/visitor-target.hpp>
#include <ast/visitor/visitor.hpp>

#include <ast/node/access-modifier.hpp>
#include <ast/node/expression.hpp>
#include <ast/node/method-argument-list.hpp>
#include <ast/node/statement-list.hpp>
#include <ast/node/type-modifier.hpp>
#include <ast/node/var-declaration-list.hpp>

namespace Ast {

class MethodDeclaration : public VisitorTarget {
 public:
  MethodDeclaration(const AccessModifier* accessModifier,
                    const TypeModifier* typeModifier,
                    const IdExpression* methodId,
                    const MethodArgumentList* methodArguments,
                    const VarDeclarationList* varDeclarations,
                    const StatementList* statements,
                    const Expression* returnExpression,
                    const Location& location)
      : VisitorTarget(location),
        accessModifier_(accessModifier),
        typeModifier_(typeModifier),
        methodId_(methodId),
        methodArguments_(methodArguments),
        varDeclarations_(varDeclarations),
        statements_(statements),
        returnExpression_(returnExpression) {}

  const AccessModifier* GetAccessModifier() const {
    return accessModifier_.get();
  }
  const TypeModifier* GetTypeModifier() const { return typeModifier_.get(); }
  const IdExpression* MethodId() const { return methodId_.get(); }
  const MethodArgumentList* MethodArguments() const {
    return methodArguments_.get();
  }
  const VarDeclarationList* VarDeclarations() const {
    return varDeclarations_.get();
  }
  const StatementList* Statements() const { return statements_.get(); }
  const Expression* ReturnExpression() const { return returnExpression_.get(); }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  std::unique_ptr<const AccessModifier> accessModifier_;
  std::unique_ptr<const TypeModifier> typeModifier_;
  std::unique_ptr<const IdExpression> methodId_;
  std::unique_ptr<const MethodArgumentList> methodArguments_;
  std::unique_ptr<const VarDeclarationList> varDeclarations_;
  std::unique_ptr<const StatementList> statements_;
  std::unique_ptr<const Expression> returnExpression_;
};

}  // namespace Ast
