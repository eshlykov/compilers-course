#pragma once

#include "wrapper.hpp"

namespace Irt {

class ExpressionWrapper : public Wrapper {
 public:
  explicit ExpressionWrapper(std::shared_ptr<Expression> expression);

  std::shared_ptr<Expression> ToRValue() const final;

  std::shared_ptr<Statement> ToCondition(Address addressIf,
                                         Address addressElse) const final;

 private:
  const std::shared_ptr<Expression> expression_;
};

inline ExpressionWrapper::ExpressionWrapper(
    std::shared_ptr<Expression> expression)
    : expression_{expression} {}

inline std::shared_ptr<Expression> ExpressionWrapper::ToRValue() const {
  return expression_;
}

inline std::shared_ptr<Statement> ExpressionWrapper::ToCondition(
    Address addressIf, Address addressElse) const {
  return std::make_shared<ConditionalJump>(LogicalOperator::Equal, expression_,
                                           std::make_shared<Constant>(1),
                                           addressIf, addressElse);
}

}  // namespace Irt
