#include "translator.hpp"
#include <memory>
#include <vector>

namespace Irt {

Translator::Translator()
    : codeFragment_{std::make_shared<Ct::CodeFragment>()} {}

void Translator::Visit(BinaryOperator* node) {
  node->leftExpression_->Accept(this);
  std::shared_ptr<Ct::Expression> leftExpression = expression_;

  node->rightExpression_->Accept(this);
  std::shared_ptr<Ct::Expression> rightExpression = expression_;

  std::optional<Ct::ArithmeticOperator> arithmeticOperator =
      ToCtArithmeticOperator(node->arithmeticOperator_);
  assert(arithmeticOperator.has_value());

  expression_ = std::make_shared<Ct::BinaryOperator>(arithmeticOperator.value(),
                                              leftExpression, rightExpression);
}

void Translator::Visit(Call* node) {
  node->expression_->Accept(this);
  std::shared_ptr<Ct::Expression> callExpression = expression_;

  std::vector<std::shared_ptr<Ct::Expression>> expressionList;
  for (const auto& expression : node->expressionList_) {
    expression->Accept(this);
    expressionList.push_back(expression_);
  }

  expression_ = std::make_shared<Ct::Call>(callExpression, expressionList);
}

void Translator::Visit(ConditionalJump* node) {
  node->expressionLeft_->Accept(this);
  std::shared_ptr<Ct::Expression> expressionLeft = expression_;

  node->expressionRight_->Accept(this);
  std::shared_ptr<Ct::Expression> expressionRight = expression_;
}

void Translator::Visit(Constant* node) {
  expression_ = std::make_shared<Ct::Constant>(node->value_);
}

void Translator::Visit(ExpressionSequence* node) {

  node->expression_->Accept(this);
  std::shared_ptr<Ct::Expression> expression = expression_;

  node->statement_->Accept(this);
  std::shared_ptr<Ct::Statement> statement = statement_;

  expression_ = std::make_shared<Ct::ExpressionSequence>(statement, expression);
}

void Translator::Visit(Jump* node) {}

void Translator::Visit(Label* node) {}

void Translator::Visit(Memory* node) {}

void Translator::Visit(Move* node) {}

void Translator::Visit(Name* node) {}

void Translator::Visit(StatementSequence* node) {}

void Translator::Visit(Temporary* node) {}

void Translator::Visit(Void* node) {}

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
