#pragma once

#include "wrapper.hpp"

namespace Irt {

class ComparisonOperatorWrapper : public Wrapper {
 public:
  ComparisonOperatorWrapper(LogicalOperator logicalOperator,
                            std::shared_ptr<Expression> leftExpression,
                            std::shared_ptr<Expression> rightExpression);

  std::shared_ptr<Expression> ToRValue() const final;

  std::shared_ptr<Statement> ToCondition(Address, Address) const override;

 protected:
  const LogicalOperator logicalOperator_;
  const std::shared_ptr<Expression> leftExpression_;
  const std::shared_ptr<Expression> rightExpression_;
};

inline ComparisonOperatorWrapper::ComparisonOperatorWrapper(
    LogicalOperator logicalOperator, std::shared_ptr<Expression> leftExpression,
    std::shared_ptr<Expression> rightExpression)
    : logicalOperator_{logicalOperator},
      leftExpression_{std::move(leftExpression)},
      rightExpression_{std::move(rightExpression)} {}

inline std::shared_ptr<Expression> ComparisonOperatorWrapper::ToRValue() const {
  Storage storage;
  Address addressIf;
  Address addressElse;
  Address addressEnd;
  return std::make_shared<ExpressionSequence>(
      ToCondition(addressIf, addressElse),
      std::make_shared<ExpressionSequence>(
          std::make_shared<StatementSequence>(
              std::make_shared<Label>(addressIf),
              std::make_shared<StatementSequence>(
                  std::make_shared<Move>(std::make_shared<Temporary>(storage),
                                         std::make_shared<Constant>(1)),
                  std::make_shared<StatementSequence>(
                      std::make_shared<Jump>(addressEnd),
                      std::make_shared<StatementSequence>(
                          std::make_shared<Label>(addressElse),
                          std::make_shared<StatementSequence>(
                              std::make_shared<Move>(
                                  std::make_shared<Temporary>(storage),
                                  std::make_shared<Constant>(0)),
                              std::make_shared<Label>(addressEnd)))))),
          std::make_shared<Temporary>(storage)));
}

inline std::shared_ptr<Statement> ComparisonOperatorWrapper::ToCondition(
    Address addressIf, Address addressElse) const {
  return std::make_shared<ConditionalJump>(logicalOperator_, leftExpression_,
                                           rightExpression_, addressIf,
                                           addressElse);
}

}  // namespace Irt
