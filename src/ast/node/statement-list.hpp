#pragma once

#include <memory>
#include <vector>

#include <ast/node/visitor-target.hpp>
#include <ast/visitor/visitor.hpp>

#include <ast/node/statement.hpp>

namespace Ast {

class StatementList : public VisitorTarget {
 public:
  StatementList(const Location& location) : VisitorTarget(location) {}
  ~StatementList() {}

  void Add(const Statement* statement) { statements_.emplace_back(statement); }

  const std::vector<std::unique_ptr<const Statement>>& Statements() const {
    return statements_;
  }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  // must be reversed before being used
  std::vector<std::unique_ptr<const Statement>> statements_;
};

}  // namespace Ast
