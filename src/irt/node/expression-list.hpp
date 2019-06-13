#pragma once

#include <memory>
#include <vector>

#include <irt/node/visitor-target.hpp>
#include <irt/visitor/visitor.hpp>

namespace Irt {

class Expression;

class ExpressionList : public IVisitorTarget {
 public:
  ExpressionList() = default;

  ExpressionList(const Expression* expression) { Add(expression); }
  ExpressionList(std::unique_ptr<const Expression> expression) {
    Add(std::move(expression));
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

  std::unique_ptr<const ExpressionList> Clone() const;

 private:
  std::vector<std::unique_ptr<const Expression>> expressions_;
};

}  // namespace Irt
