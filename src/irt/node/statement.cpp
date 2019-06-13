#include <cassert>
#include <irt/node/expression.hpp>
#include <irt/node/statement.hpp>

using namespace Irt;

Statement::~Statement() {}

MoveStatement::MoveStatement(const Expression* destination,
                             const Expression* source)
    : destination_(destination), source_(source) {}
MoveStatement::MoveStatement(std::unique_ptr<const Expression> destination,
                             std::unique_ptr<const Expression> source)
    : destination_(std::move(destination)), source_(std::move(source)) {}
MoveStatement::~MoveStatement() {}

std::unique_ptr<const Statement> MoveStatement::Clone() const {
  return std::move(std::unique_ptr<const Statement>(
      new MoveStatement(destination_->Clone(), source_->Clone())));
}

ExpStatement::ExpStatement(const Expression* expression)
    : expression_(expression) {}
ExpStatement::ExpStatement(std::unique_ptr<const Expression> expression)
    : expression_(std::move(expression)) {}
ExpStatement::~ExpStatement() {}

std::unique_ptr<const Statement> ExpStatement::Clone() const {
  return std::move(
      std::unique_ptr<const Statement>(new ExpStatement(expression_->Clone())));
}

JumpStatement::JumpStatement(Address target) : target_(std::move(target)) {}
JumpStatement::~JumpStatement() {}

std::unique_ptr<const Statement> JumpStatement::Clone() const {
  return std::move(
      std::unique_ptr<const Statement>(new JumpStatement(target_)));
}

JumpConditionalStatement::JumpConditionalStatement(LogicOperatorTypes operation,
                                                   const Expression* left,
                                                   const Expression* right,
                                                   Address labelTrue,
                                                   Address labelFalse)
    : leftOperand_(left),
      rightOperand_(right),
      labelTrue_(std::move(labelTrue)),
      labelFalse_(std::move(labelFalse)),
      operation_(operation) {}
JumpConditionalStatement::JumpConditionalStatement(
    LogicOperatorTypes operation, std::unique_ptr<const Expression> left,
    std::unique_ptr<const Expression> right, Address labelTrue,
    Address labelFalse)
    : leftOperand_(std::move(left)),
      rightOperand_(std::move(right)),
      labelTrue_(std::move(labelTrue)),
      labelFalse_(std::move(labelFalse)),
      operation_(operation) {}
JumpConditionalStatement::~JumpConditionalStatement() {}

std::unique_ptr<const Statement> JumpConditionalStatement::Clone() const {
  return std::move(
      std::unique_ptr<const Statement>(new JumpConditionalStatement(
          operation_, leftOperand_->Clone(), rightOperand_->Clone(), labelTrue_,
          labelFalse_)));
}

SeqStatement::SeqStatement(const Statement* left, const Statement* right)
    : leftStatement_(left), rightStatement_(right) {}
SeqStatement::SeqStatement(std::unique_ptr<const Statement> left,
                           std::unique_ptr<const Statement> right)
    : leftStatement_(std::move(left)), rightStatement_(std::move(right)) {}
SeqStatement::~SeqStatement() {}

std::unique_ptr<const Statement> SeqStatement::Clone() const {
  return std::move(std::unique_ptr<const Statement>(
      new SeqStatement(leftStatement_->Clone(), rightStatement_->Clone())));
}

LabelStatement::LabelStatement(Address label) : label_(std::move(label)) {}
LabelStatement::~LabelStatement() {}

std::unique_ptr<const Statement> LabelStatement::Clone() const {
  return std::move(
      std::unique_ptr<const Statement>(new LabelStatement(label_)));
}

std::unique_ptr<const Statement> StatementList::Clone() const {
  StatementList* newList = new StatementList();
  for (auto it = statements_.begin(); it != statements_.end(); ++it) {
    newList->Add(std::move((*it)->Clone()));
  }
  return std::move(std::unique_ptr<const StatementList>(newList));
}
