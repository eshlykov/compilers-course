#pragma once

#include <memory>
#include <vector>

#include <ast/node/visitor-target.hpp>
#include <ast/visitor/visitor.hpp>

#include <ast/node/expression.hpp>
#include <ast/node/method-argument.hpp>
#include <ast/node/type-modifier.hpp>

namespace Ast {

class MethodArgumentList : public VisitorTarget {
 public:
  MethodArgumentList(const Location& location) : VisitorTarget(location) {}

  void Add(const MethodArgument* argument) {
    arguments_.emplace_back(argument);
  }

  const std::vector<std::unique_ptr<const MethodArgument>>& MethodArguments()
      const {
    return arguments_;
  }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  std::vector<std::unique_ptr<const MethodArgument>> arguments_;
};

}  // namespace Ast
