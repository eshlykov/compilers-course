#include "translator.hpp"
#include <memory>
#include <vector>

namespace Irt {

Translator::Translator()
    : codeFragment_{std::make_shared<Ct::CodeFragment>()} {}

void Translator::Visit(BinaryOperator* node) {
  node->leftExpression_->Accept(this);
  std::shared_ptr<Ct::Expression> leftExpression = exp_;

  node->rightExpression_->Accept(this);
  std::shared_ptr<Ct::Expression> rightExpression = exp_;

  std::optional<Ct::ArithmeticOperator> arithmeticOperator =
      ToCtArithmeticOperator(node->arithmeticOperator_);
  assert(arithmeticOperator.has_value());

  exp_ = std::make_shared<Ct::BinaryOperator>(arithmeticOperator.value(),
                                              leftExpression, rightExpression);
}

void Translator::Visit(Call* node) {
  node->expression_->Accept(this);
  std::shared_ptr<Ct::Expression> callExpression = exp_;

  std::vector<std::shared_ptr<Ct::Expression>> expressionList;
  for (const auto& expression : node->expressionList_) {
    expression->Accept(this);
    expressionList.push_back(exp_);
  }

  exp_ = std::make_shared<Ct::Call>(callExpression, expressionList);
}

void Translator::Visit(ConditionalJump* node) {
  node->expressionLeft_->Accept(this);
  std::shared_ptr<Ct::Expression> expressionLeft = exp_;

  node->expressionRight_->Accept(this);
  std::shared_ptr<Ct::Expression> expressionRight = exp_;
}

void Translator::Visit(Constant* node) {}

void Translator::Visit(ExpressionSequence* node) {}

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
    return Ct::ArithmeticOperator::Plus;
  } else if (arithmeticOperator == ArithmeticOperator::Minus) {
    return Ct::ArithmeticOperator::Minus;
  } else if (arithmeticOperator == ArithmeticOperator::Multiplication) {
    return Ct::ArithmeticOperator::Multiplication;
  }
  return {};
}

std::optional<Ct::LogicalOperator> Translator::ToCtLogicalOperator(
    LogicalOperator logicalOperator) {
  if (logicalOperator == LogicalOperator::And) {
    return Ct::LogicalOperator::And;
  } else if (logicalOperator == LogicalOperator::Less) {
    return Ct::LogicalOperator::Less;
  } else if (logicalOperator == LogicalOperator::Equal) {
    return Ct::LogicalOperator::Equal;
  }

  return {};
}

}  // namespace Irt
