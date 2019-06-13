#pragma once

#include <memory>

#include <utils/address.hpp>
#include <utils/storage.hpp>

#include <irt/visitor/visitor.hpp>

#include <irt/node/expression-list.hpp>
#include <irt/node/statement.hpp>
#include <irt/node/visitor-target.hpp>

namespace Irt {

class Expression : public IVisitorTarget {
 public:
  virtual ~Expression();
  virtual std::unique_ptr<const Expression> Clone() const = 0;
};

enum class OperatorTypes : char { Plus, Minus, Times, Div, Mod, And, Or };

//-----------------------------------------------------------------------------------------------//

class ConstExpression : public Expression {
 public:
  ConstExpression(int value);
  ~ConstExpression();

  int Value() const { return value_; }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  std::unique_ptr<const Expression> Clone() const override;

 private:
  int value_;
};

//-----------------------------------------------------------------------------------------------//

class NameExpression : public Expression {
 public:
  NameExpression(Address address);
  ~NameExpression();

  Address GetAddress() const { return address_; }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  std::unique_ptr<const Expression> Clone() const override;

 private:
  Address address_;
};

//-----------------------------------------------------------------------------------------------//

class TempExpression : public Expression {
 public:
  TempExpression(const Storage& storage);
  ~TempExpression();

  Storage GetStorage() const { return storage_; }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  std::unique_ptr<const Expression> Clone() const override;

 private:
  Storage storage_;
};

//-----------------------------------------------------------------------------------------------//

class BinaryExpression : public Expression {
 public:
  BinaryExpression(OperatorTypes operation, const Expression* left,
                   const Expression* right);
  BinaryExpression(OperatorTypes operation,
                   std::unique_ptr<const Expression> left,
                   std::unique_ptr<const Expression> right);
  ~BinaryExpression();

  OperatorTypes Operation() const { return operation_; }
  const Expression* LeftOperand() const { return leftOperand_.get(); }
  const Expression* RightOperand() const { return rightOperand_.get(); }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  std::unique_ptr<const Expression> Clone() const override;

 private:
  std::unique_ptr<const Expression> leftOperand_;
  std::unique_ptr<const Expression> rightOperand_;
  OperatorTypes operation_;
};

//-----------------------------------------------------------------------------------------------//

class MemExpression : public Expression {
 public:
  MemExpression(const Expression* address);
  MemExpression(std::unique_ptr<const Expression> address);
  ~MemExpression();

  const Expression* Address() const { return address_.get(); }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  std::unique_ptr<const Expression> Clone() const override;

 private:
  std::unique_ptr<const Expression> address_;
};

//-----------------------------------------------------------------------------------------------//

class CallExpression : public Expression {
 public:
  CallExpression(const Expression* func, const ExpressionList* args);
  CallExpression(std::unique_ptr<const Expression> func,
                 std::unique_ptr<const ExpressionList> args);
  ~CallExpression();

  const Expression* Function() const { return function_.get(); }
  const ExpressionList* Arguments() const { return arguments_.get(); }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  std::unique_ptr<const Expression> Clone() const override;

 private:
  std::unique_ptr<const Expression> function_;
  std::unique_ptr<const ExpressionList> arguments_;
};

//-----------------------------------------------------------------------------------------------//
class EseqExpression : public Expression {
 public:
  EseqExpression(const Statement* statement, const Expression* expression);
  EseqExpression(std::unique_ptr<const Statement> statement,
                 std::unique_ptr<const Expression> expression);
  ~EseqExpression();

  const Statement* GetStatement() const { return statement_.get(); }
  const Expression* GetExpression() const { return expression_.get(); }

  void Accept(IVisitor* visitor) const override { visitor->Visit(this); }

  std::unique_ptr<const Expression> Clone() const override;

 private:
  std::unique_ptr<const Statement> statement_;
  std::unique_ptr<const Expression> expression_;
};

}  // namespace Irt
