#include "translator.hpp"
#include <memory>
#include <vector>

namespace Irt {

Translator::Translator()
    : codeFragment_{std::make_shared<Ct::CodeFragment>()} {}

void Translator::Visit(BinaryOperator *node) {
  node->leftExpression_->Accept(this);
  std::shared_ptr<Ct::Expression> leftExpression = expression_;

  node->rightExpression_->Accept(this);
  std::shared_ptr<Ct::Expression> rightExpression = expression_;

  std::optional<Ct::ArithmeticOperator> arithmeticOperator =
      ToCtArithmeticOperator(node->arithmeticOperator_);
  assert(arithmeticOperator.has_value());

  expression_ = std::make_shared<Ct::BinaryOperator>(
      arithmeticOperator.value(), leftExpression, rightExpression);
}

void Translator::Visit(Call *node) {
  node->expression_->Accept(this);
  std::shared_ptr<Ct::Expression> callExpression = expression_;

  std::vector<std::shared_ptr<Ct::Expression>> expressionList;
  for (const auto &expression : node->expressionList_) {
    expression->Accept(this);
    expressionList.push_back(expression_);
  }

  expression_ = std::make_shared<Ct::Call>(callExpression, expressionList);
}

void Translator::Visit(ConditionalJump *node) {
  node->expressionLeft_->Accept(this);
  std::shared_ptr<Ct::Expression> expressionLeft = expression_;

  node->expressionRight_->Accept(this);
  std::shared_ptr<Ct::Expression> expressionRight = expression_;
}

void Translator::Visit(Constant *node) {
  expression_ = std::make_shared<Ct::Constant>(node->value_);
}

void Translator::Visit(ExpressionSequence *node) {
  node->expression_->Accept(this);
  std::shared_ptr<Ct::Expression> expression = expression_;

  node->statement_->Accept(this);
  std::shared_ptr<Ct::Statement> statement = statement_;

  expression_ = std::make_shared<Ct::ExpressionSequence>(statement, expression);
}

void Translator::Visit(Jump *node) {
  statement_ = std::make_shared<Ct::Jump>(node->address_);
}

void Translator::Visit(Label *node) {
  statement_ = std::make_shared<Ct::Label>(node->address_);
}

void Translator::Visit(Memory *node) {
  node->expression_->Accept(this);
  std::shared_ptr<Ct::Expression> expression = expression_;

  expression_ = std::make_shared<Ct::Memory>(expression);
}

void Translator::Visit(Move *node) {
  node->destination_->Accept(this);
  std::shared_ptr<Ct::Expression> destination = expression_;

  node->source_->Accept(this);
  std::shared_ptr<Ct::Expression> source = expression_;

  statement_ = std::make_shared<Ct::Move>(destination, source);
}

void Translator::Visit(Name *node) {
  expression_ = std::make_shared<Ct::Name>(node->address_);
}

void Translator::Visit(StatementSequence *node) {
  node->leftStatement_->Accept(this);
  std::shared_ptr<Ct::Statement> leftStatement = statement_;

  node->rightStatement_->Accept(this);
  std::shared_ptr<Ct::Statement> rightStatement = statement_;

  statement_ =
      std::make_shared<Ct::StatementSequence>(leftStatement, rightStatement);
}

void Translator::Visit(Temporary *node) {
  expression_ = std::make_shared<Ct::Temporary>(node->storage_);
}

void Translator::Visit(Void *node) {
  node->expression_->Accept(this);
  std::shared_ptr<Ct::Expression> expression = expression_;
  statement_ = std::make_shared<Ct::Void>(expression);
}

std::optional<Ct::ArithmeticOperator> Translator::ToCtArithmeticOperator(
    ArithmeticOperator arithmeticOperator) {
  if (arithmeticOperator == ArithmeticOperator::Plus) {
    return {Ct::ArithmeticOperator::Plus};
  } else if (arithmeticOperator == ArithmeticOperator::Minus) {
    return {Ct::ArithmeticOperator::Minus};
  } else if (arithmeticOperator == ArithmeticOperator::Multiplication) {
    return {Ct::ArithmeticOperator::Multiplication};
  }
  return {};
}

std::optional<Ct::LogicalOperator> Translator::ToCtLogicalOperator(
    LogicalOperator logicalOperator) {
  if (logicalOperator == LogicalOperator::And) {
    return {Ct::LogicalOperator::And};
  } else if (logicalOperator == LogicalOperator::Less) {
    return {Ct::LogicalOperator::Less};
  } else if (logicalOperator == LogicalOperator::Equal) {
    return {Ct::LogicalOperator::Equal};
  }

  return {};
}

}  // namespace Irt
