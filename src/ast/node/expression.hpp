#pragma once

#include <memory>
#include <string>

#include <ast/node/visitor-target.hpp>
#include <ast/visitor/visitor.hpp>

#include <ast/node/expression-list.hpp>

namespace Ast {

class Expression : public VisitorTarget {
 public:
  explicit Expression(const Location& location) : VisitorTarget(location) {}
};

//-----------------------------------------------------------------------------------------------//
//
enum class OperatorTypes : char { Plus, Minus, Times, Div, Mod, Less, And, Or };

class BinaryExpression : public Expression {
 public:
  BinaryExpression(OperatorTypes operation, const Expression* left,
                   const Expression* right, const Location& location)
      : Expression(location),
        operation_(operation),
        leftOperand_(left),
        rightOperand_(right) {}

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  OperatorTypes Operation() const { return operation_; }
  const Expression* LeftOperand() const { return leftOperand_.get(); }
  const Expression* RightOperand() const { return rightOperand_.get(); }

 private:
  std::unique_ptr<const Expression> leftOperand_;
  std::unique_ptr<const Expression> rightOperand_;
  OperatorTypes operation_;
};

//-----------------------------------------------------------------------------------------------//

// a[b]
class BracketExpression : public Expression {
 public:
  BracketExpression(const Expression* containerExpression,
                    const Expression* indexExpression, const Location& location)
      : Expression(location),
        containerExpression_(containerExpression),
        indexExpression_(indexExpression) {}

  const Expression* ContainerExpression() const {
    return containerExpression_.get();
  }
  const Expression* IndexExpression() const { return indexExpression_.get(); }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  std::unique_ptr<const Expression> containerExpression_;  // a
  std::unique_ptr<const Expression> indexExpression_;      // b
};

//-----------------------------------------------------------------------------------------------//

class NumberExpression : public Expression {
 public:
  NumberExpression(int value, const Location& location)
      : Expression(location), value_(value) {}

  int Value() const { return value_; }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  int value_;
};

//-----------------------------------------------------------------------------------------------//

class LogicExpression : public Expression {
 public:
  LogicExpression(bool value, const Location& location)
      : Expression(location), value_(value) {}

  bool Value() const { return value_; }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  bool value_;
};

//----------------------------------------------------------------------------------------------//

// Expression for identities (variables)
class IdExpression : public Expression {
 public:
  IdExpression(std::string name, const Location& location)
      : Expression(location), name_(std::move(name)) {}

  const std::string& Name() const { return name_; }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  std::string name_;
};

//----------------------------------------------------------------------------------------------//

class LengthExpression : public Expression {
 public:
  LengthExpression(const Expression* lengthTarget, const Location& location)
      : Expression(location), lengthTarget_(lengthTarget) {}

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  const Expression* LengthTarget() const { return lengthTarget_.get(); }

 private:
  std::unique_ptr<const Expression> lengthTarget_;
};

//-----------------------------------------------------------------------------------------------//

class MethodExpression : public Expression {
 public:
  MethodExpression(const Expression* callerExpression,
                   const IdExpression* methodId,
                   const ExpressionList* arguments, const Location& location)
      : Expression(location),
        callerExpression_(callerExpression),
        methodId_(methodId),
        arguments_(arguments) {}

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  const Expression* CallerExpression() const { return callerExpression_.get(); }
  const IdExpression* MethodId() const { return methodId_.get(); }
  const ExpressionList* Arguments() const { return arguments_.get(); }

 private:
  std::unique_ptr<const Expression> callerExpression_;
  std::unique_ptr<const IdExpression> methodId_;
  std::unique_ptr<const ExpressionList> arguments_;
};

//-----------------------------------------------------------------------------------------------//

class ThisExpression : public Expression {
 public:
  explicit ThisExpression(const Location& location) : Expression(location) {}

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }
};

//-----------------------------------------------------------------------------------------------//

class NewArrayExpression : public Expression {
 public:
  NewArrayExpression(const Expression* lengthExpression,
                     const Location& location)
      : Expression(location), lengthExpression_(lengthExpression) {}

  const Expression* LengthExpression() const { return lengthExpression_.get(); }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  std::unique_ptr<const Expression> lengthExpression_;
};

//-----------------------------------------------------------------------------------------------//

class NewIdExpression : public Expression {
 public:
  NewIdExpression(const IdExpression* targetId, const Location& location)
      : Expression(location), targetId_(targetId) {}

  const IdExpression* TargetId() const { return targetId_.get(); }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  std::unique_ptr<const IdExpression> targetId_;
};

//-----------------------------------------------------------------------------------------------//

class NegateExpression : public Expression {
 public:
  NegateExpression(const Expression* targetExpression, const Location& location)
      : Expression(location), targetExpression_(targetExpression) {}

  const Expression* TargetExpression() const { return targetExpression_.get(); }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

 private:
  std::unique_ptr<const Expression> targetExpression_;
};

}  // namespace Ast
