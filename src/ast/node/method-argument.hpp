#pragma once

#include <memory>
#include <vector>

#include <ast/node/visitor-target.hpp>
#include <ast/visitor/visitor.hpp>

#include <ast/node/expression.hpp>
#include <ast/node/type-modifier.hpp>

namespace Ast {

class MethodArgument : public VisitorTarget {
 public:
  MethodArgument(const TypeModifier* type, const IdExpression* id,
                 const Location& location)
      : VisitorTarget(location), type_(type), id_(id) {}

  const TypeModifier* Type() const { return type_.get(); }
  const IdExpression* Id() const { return id_.get(); }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  std::unique_ptr<const TypeModifier> type_;
  std::unique_ptr<const IdExpression> id_;
};

}  // namespace Ast
