#include <cassert>
#include <irt/node/expression.hpp>
#include <irt/node/statement.hpp>

using namespace Irt;

Expression::~Expression() {}

ConstExpression::ConstExpression(int value) : value_(value) {}
ConstExpression::~ConstExpression() {}

std::unique_ptr<const Expression> ConstExpression::Clone() const {
  return std::move(
      std::unique_ptr<const Expression>(new ConstExpression(value_)));
}

NameExpression::NameExpression(Address address) : address_(address) {}
NameExpression::~NameExpression() {}

std::unique_ptr<const Expression> NameExpression::Clone() const {
  return std::move(
      std::unique_ptr<const Expression>(new NameExpression(address_)));
}

TempExpression::TempExpression(const Storage& storage) : storage_(storage) {}
TempExpression::~TempExpression() {}

std::unique_ptr<const Expression> TempExpression::Clone() const {
  return std::move(
      std::unique_ptr<const Expression>(new TempExpression(storage_)));
}

BinaryExpression::BinaryExpression(OperatorTypes operation,
                                   const Expression* left,
                                   const Expression* right)
    : operation_(operation), leftOperand_(left), rightOperand_(right) {}
BinaryExpression::BinaryExpression(OperatorTypes operation,
                                   std::unique_ptr<const Expression> left,
                                   std::unique_ptr<const Expression> right)
    : operation_(operation),
      leftOperand_(std::move(left)),
      rightOperand_(std::move(right)) {}
BinaryExpression::~BinaryExpression() {}

std::unique_ptr<const Expression> BinaryExpression::Clone() const {
  return std::move(std::unique_ptr<const Expression>(new BinaryExpression(
      operation_, leftOperand_->Clone(), rightOperand_->Clone())));
}

MemExpression::MemExpression(const Expression* address) : address_(address) {}
MemExpression::MemExpression(std::unique_ptr<const Expression> address)
    : address_(std::move(address)) {}
MemExpression::~MemExpression() {}

std::unique_ptr<const Expression> MemExpression::Clone() const {
  return std::move(
      std::unique_ptr<const Expression>(new MemExpression(address_->Clone())));
}

CallExpression::CallExpression(const Expression* func,
                               const ExpressionList* args)
    : function_(func), arguments_(args) {}
CallExpression::CallExpression(std::unique_ptr<const Expression> func,
                               std::unique_ptr<const ExpressionList> args)
    : function_(std::move(func)), arguments_(std::move(args)) {}
CallExpression::~CallExpression() {}

std::unique_ptr<const Expression> CallExpression::Clone() const {
  return std::move(std::unique_ptr<const Expression>(
      new CallExpression(function_->Clone(), arguments_->Clone())));
}

EseqExpression::EseqExpression(const Statement* statement,
                               const Expression* expression)
    : statement_(statement), expression_(expression) {}
EseqExpression::EseqExpression(std::unique_ptr<const Statement> statement,
                               std::unique_ptr<const Expression> expression)
    : statement_(std::move(statement)), expression_(std::move(expression)) {}
EseqExpression::~EseqExpression() {}

std::unique_ptr<const Expression> EseqExpression::Clone() const {
  return std::move(std::unique_ptr<const Expression>(
      new EseqExpression(statement_->Clone(), expression_->Clone())));
}
