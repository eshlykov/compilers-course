#pragma once

#include <cassert>
#include <irt/node/expression.hpp>
#include <irt/node/statement.hpp>
#include <memory>
#include <utils/address.hpp>

namespace Irt {

// Base Subtree Wrappers

class ISubtreeWrapper {
 public:
  virtual ~ISubtreeWrapper() = default;
  virtual std::unique_ptr<const Expression> ToExpression() = 0;
  virtual std::unique_ptr<const Statement> ToStatement() = 0;
  virtual std::unique_ptr<const Statement> ToConditional(
      Address labelTrue, Address labelFalse) = 0;
};

class ExpressionWrapper : public ISubtreeWrapper {
 public:
  explicit ExpressionWrapper(const Expression* expression)
      : expression_(expression) {}
  explicit ExpressionWrapper(std::unique_ptr<const Expression> expression)
      : expression_(std::move(expression)) {}
  virtual ~ExpressionWrapper() = default;

  virtual std::unique_ptr<const Expression> ToExpression() override;
  virtual std::unique_ptr<const Statement> ToStatement() override;
  virtual std::unique_ptr<const Statement> ToConditional(
      Address labelTrue, Address labelFalse) override;

 private:
  std::unique_ptr<const Expression> expression_;
};

class StatementWrapper : public ISubtreeWrapper {
 public:
  explicit StatementWrapper(const Statement* statement)
      : statement_(statement) {}
  explicit StatementWrapper(std::unique_ptr<const Statement> statement)
      : statement_(std::move(statement)) {}
  virtual ~StatementWrapper() = default;

  virtual std::unique_ptr<const Expression> ToExpression() override;
  virtual std::unique_ptr<const Statement> ToStatement() override;
  virtual std::unique_ptr<const Statement> ToConditional(
      Address labelTrue, Address labelFalse) override;

 private:
  std::unique_ptr<const Statement> statement_;
};

class ConditionalWrapper : public ISubtreeWrapper {
 public:
  ConditionalWrapper() = default;
  virtual ~ConditionalWrapper() = default;

  virtual std::unique_ptr<const Expression> ToExpression() override;
  virtual std::unique_ptr<const Statement> ToStatement() override;
  virtual std::unique_ptr<const Statement> ToConditional(
      Address labelTrue, Address labelFalse) override = 0;
};

// Specific Subtree Wrappers

class RelativeConditionalWrapper : public ConditionalWrapper {
 public:
  RelativeConditionalWrapper(LogicOperatorTypes operatorType,
                             const Expression* operandLeft,
                             const Expression* operandRight)
      : operatorType_(operatorType),
        operandLeft_(operandLeft),
        operandRight_(operandRight) {}

  RelativeConditionalWrapper(LogicOperatorTypes operatorType,
                             std::unique_ptr<const Expression> operandLeft,
                             std::unique_ptr<const Expression> operandRight)
      : operatorType_(operatorType),
        operandLeft_(std::move(operandLeft)),
        operandRight_(std::move(operandRight)) {}

  virtual std::unique_ptr<const Statement> ToConditional(
      Address labelTrue, Address labelFalse) override;

 private:
  LogicOperatorTypes operatorType_;
  std::unique_ptr<const Expression> operandLeft_;
  std::unique_ptr<const Expression> operandRight_;
};

class AndConditionalWrapper : public ConditionalWrapper {
 public:
  AndConditionalWrapper(std::unique_ptr<ISubtreeWrapper> operandLeft,
                        std::unique_ptr<ISubtreeWrapper> operandRight)
      : operandLeft_(std::move(operandLeft)),
        operandRight_(std::move(operandRight)) {}

  virtual std::unique_ptr<const Statement> ToConditional(
      Address labelTrue, Address labelFalse) override;

 private:
  std::unique_ptr<ISubtreeWrapper> operandLeft_;
  std::unique_ptr<ISubtreeWrapper> operandRight_;
};

class OrConditionalWrapper : public ConditionalWrapper {
 public:
  OrConditionalWrapper(std::unique_ptr<ISubtreeWrapper> operandLeft,
                       std::unique_ptr<ISubtreeWrapper> operandRight)
      : operandLeft_(std::move(operandLeft)),
        operandRight_(std::move(operandRight)) {}

  virtual std::unique_ptr<const Statement> ToConditional(
      Address labelTrue, Address labelFalse) override;

 private:
  std::unique_ptr<ISubtreeWrapper> operandLeft_;
  std::unique_ptr<ISubtreeWrapper> operandRight_;
};

class NegateConditionalWrapper : public ConditionalWrapper {
 public:
  NegateConditionalWrapper(std::unique_ptr<ISubtreeWrapper> wrapper)
      : wrapper_(std::move(wrapper)) {}

  virtual std::unique_ptr<const Statement> ToConditional(
      Address labelTrue, Address labelFalse) override;

 private:
  std::unique_ptr<ISubtreeWrapper> wrapper_;
};

std::unique_ptr<const Expression> ExpressionWrapper::ToExpression() {
  return std::move(expression_);
}

std::unique_ptr<const Statement> ExpressionWrapper::ToStatement() {
  return std::move(std::unique_ptr<const Statement>(
      new ExpStatement(std::move(expression_))));
}

std::unique_ptr<const Statement> ExpressionWrapper::ToConditional(
    Address labelTrue, Address labelFalse) {
  return std::move(
      std::unique_ptr<const Statement>(new JumpConditionalStatement(
          LogicOperatorTypes::NotEqual, std::move(expression_),
          std::move(std::unique_ptr<const Expression>(new ConstExpression(0))),
          labelTrue, labelFalse)));
}

std::unique_ptr<const Expression> StatementWrapper::ToExpression() {
  // such calls should never happen
  assert(false);
  // return std::move( std::unique_ptr<const CExpression>(
  //     new CEseqExpression( statement, new CConstExpression( 0 ) )
  // ) );
}

std::unique_ptr<const Statement> StatementWrapper::ToStatement() {
  return std::move(statement_);
}

std::unique_ptr<const Statement> StatementWrapper::ToConditional(
    Address labelTrue, Address labelFalse) {
  // such calls should never happen
  assert(false);
}

std::unique_ptr<const Expression> ConditionalWrapper::ToExpression() {
  TempExpression* tempExpression = new TempExpression(Storage());
  Address labelFalse;
  Address labelTrue;
  return std::move(std::unique_ptr<const Expression>(new EseqExpression(
      new SeqStatement(
          new MoveStatement(tempExpression, new ConstExpression(1)),
          new SeqStatement(
              std::move(ToConditional(labelTrue, labelFalse)),
              std::move(std::unique_ptr<const SeqStatement>(new SeqStatement(
                  new LabelStatement(labelFalse),
                  new SeqStatement(
                      new MoveStatement(tempExpression, new ConstExpression(0)),
                      new LabelStatement(labelTrue))))))),
      tempExpression)));
}

std::unique_ptr<const Statement> ConditionalWrapper::ToStatement() {
  /* TODO; */
  assert(false);
}

std::unique_ptr<const Statement> RelativeConditionalWrapper::ToConditional(
    Address labelTrue, Address labelFalse) {
  return std::move(
      std::unique_ptr<const Statement>(new JumpConditionalStatement(
          operatorType_, std::move(operandLeft_), std::move(operandRight_),
          labelTrue, labelFalse)));
}

std::unique_ptr<const Statement> AndConditionalWrapper::ToConditional(
    Address labelTrue, Address labelFalse) {
  Address labelMiddle;
  return std::move(std::unique_ptr<const Statement>(new SeqStatement(
      std::move(operandLeft_->ToConditional(labelMiddle, labelFalse)),
      std::move(std::unique_ptr<const SeqStatement>(new SeqStatement(
          std::move(std::unique_ptr<const LabelStatement>(
              new LabelStatement(labelMiddle))),
          std::move(operandRight_->ToConditional(labelTrue, labelFalse))))))));
}

std::unique_ptr<const Statement> OrConditionalWrapper::ToConditional(
    Address labelTrue, Address labelFalse) {
  Address labelMiddle;
  return std::move(std::unique_ptr<const Statement>(new SeqStatement(
      std::move(operandLeft_->ToConditional(labelTrue, labelMiddle)),
      std::move(std::unique_ptr<const SeqStatement>(new SeqStatement(
          std::move(std::unique_ptr<const LabelStatement>(
              new LabelStatement(labelMiddle))),
          std::move(operandRight_->ToConditional(labelTrue, labelFalse))))))));
}

std::unique_ptr<const Statement> NegateConditionalWrapper::ToConditional(
    Address labelTrue, Address labelFalse) {
  return std::move(wrapper_->ToConditional(
      labelFalse, labelTrue));  // reversed order of arguments
}

}  // namespace Irt
