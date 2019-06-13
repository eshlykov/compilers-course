#pragma once

#include <ast/node/visitor-target.hpp>
#include <ast/visitor/visitor.hpp>

namespace Ast {

class AccessModifier : public VisitorTarget {
 public:
  explicit AccessModifier(const Location& location) : VisitorTarget(location) {}
  virtual ~AccessModifier() = default;
};

class PublicAccessModifier : public AccessModifier {
 public:
  explicit PublicAccessModifier(const Location& location)
      : AccessModifier(location) {}
  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }
};

class PrivateAccessModifier : public AccessModifier {
 public:
  explicit PrivateAccessModifier(const Location& location)
      : AccessModifier(location) {}
  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }
};

}  // namespace Ast
