#pragma once

#include <memory>
#include "../../utils/address.hpp"
#include "expression.hpp"
#include "statement.hpp"

namespace Ct {

enum class LogicalOperator { And, Less, Equal, NotLess, NotEqual };

class ConditionalJump : public Statement {
 public:
  ConditionalJump(LogicalOperator logicalOperator, ExpressionPtr expressionLeft,
                  ExpressionPtr expressionRight, Address addressIf,
                  Address addressElse);

  void Accept(Visitor* visitor) final;

  std::vector<ExpressionPtr> Kids() final;

  StatementPtr Build(const std::vector<ExpressionPtr>& expressionList) final;

 public:
  const LogicalOperator logicalOperator_;
  const ExpressionPtr expressionLeft_;
  const ExpressionPtr expressionRight_;
  const Address addressIf_;
  const Address addressElse_;
};

inline ConditionalJump::ConditionalJump(LogicalOperator logicalOperator,
                                        ExpressionPtr expressionLeft,
                                        ExpressionPtr expressionRight,
                                        Address addressIf, Address addressElse)
    : logicalOperator_{logicalOperator},
      expressionLeft_{std::move(expressionLeft)},
      expressionRight_{std::move(expressionRight)},
      addressIf_{std::move(addressIf)},
      addressElse_{std::move(addressElse)} {
  assert(expressionLeft_ != nullptr);
  assert(expressionRight_ != nullptr);
}

inline void ConditionalJump::Accept(Visitor* visitor) { visitor->Visit(this); }

inline std::vector<ExpressionPtr> ConditionalJump::Kids() {
  return {expressionLeft_, expressionRight_};
}

inline StatementPtr ConditionalJump::Build(
    const std::vector<ExpressionPtr>& expressionList) {
  return std::make_shared<ConditionalJump>(logicalOperator_, expressionList[0],
                                           expressionList[1], addressIf_,
                                           addressElse_);
}

inline LogicalOperator InverseLogicalOperator(LogicalOperator logicalOperator) {
  switch (logicalOperator) {
    case LogicalOperator::Equal:
      return LogicalOperator::NotEqual;
    case LogicalOperator::NotEqual:
      return LogicalOperator ::Equal;
    case LogicalOperator::Less:
      return LogicalOperator ::NotLess;
    case LogicalOperator::NotLess:
      return LogicalOperator ::Less;
    default:
      std::abort();
  }
}

using ConditionalJumpPtr = std::shared_ptr<ConditionalJump>;

}  // namespace Ct
