#pragma once

#include <memory>

#include <ast/node/visitor-target.hpp>
#include <ast/visitor/visitor.hpp>

#include <ast/node/expression.hpp>
#include <ast/node/statement-list.hpp>

namespace Ast {

class MainClass : public VisitorTarget {
 public:
  MainClass(const IdExpression* className, const IdExpression* classArgsName,
            const StatementList* statements, const Location& location)
      : VisitorTarget(location),
        className_(className),
        classArgsName_(classArgsName),
        statements_(statements) {}

  const IdExpression* ClassName() const { return className_.get(); }
  const IdExpression* ClassArgsName() const { return classArgsName_.get(); }
  const StatementList* Statements() const { return statements_.get(); }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  std::unique_ptr<const IdExpression> className_;
  std::unique_ptr<const IdExpression> classArgsName_;
  std::unique_ptr<const StatementList> statements_;
};

}  // namespace Ast
