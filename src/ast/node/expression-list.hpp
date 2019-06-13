#pragma once

#include <memory>
#include <vector>

#include <ast/node/visitor-target.hpp>
#include <ast/visitor/visitor.hpp>

namespace Ast {

class Expression;

class ExpressionList : public VisitorTarget {
 public:
  ExpressionList(const Location& location) : VisitorTarget(location) {}

  ExpressionList(const Expression* expression, const Location& location)
      : VisitorTarget(location) {
    Add(expression);
  }

  void Add(const Expression* expression) {
    expressions_.emplace_back(expression);
  }

  void Add(std::unique_ptr<const Expression> expression) {
    expressions_.push_back(std::move(expression));
  }

  const std::vector<std::unique_ptr<const Expression>>& Expressions() const {
    return expressions_;
  }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  std::vector<std::unique_ptr<const Expression>> expressions_;
};

}  // namespace Ast
