#pragma once

#include <memory>

#include <ast/node/visitor-target.hpp>
#include <ast/visitor/visitor.hpp>

#include <ast/node/expression.hpp>

namespace Ast {

class TypeModifier : public VisitorTarget {
 public:
  TypeModifier(const Location& location) : VisitorTarget(location) {}
  virtual ~TypeModifier() {}
};

class IntTypeModifier : public TypeModifier {
 public:
  explicit IntTypeModifier(const Location& location) : TypeModifier(location) {}
  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }
};

class BooleanTypeModifier : public TypeModifier {
 public:
  explicit BooleanTypeModifier(const Location& location)
      : TypeModifier(location) {}
  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }
};

class IntArrayTypeModifier : public TypeModifier {
 public:
  explicit IntArrayTypeModifier(const Location& location)
      : TypeModifier(location) {}
  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }
};

class IdTypeModifier : public TypeModifier {
 public:
  IdTypeModifier(const IdExpression* typeId, const Location& location)
      : TypeModifier(location), typeId_(typeId) {}

  const IdExpression* TypeId() const { return typeId_.get(); }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  std::unique_ptr<const IdExpression> typeId_;
};

}  // namespace Ast
