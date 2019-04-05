#pragma once

#include <memory>
#include "../../utils/address.hpp"
#include "statement.hpp"

namespace Ct {

class Expression;

enum class LogicalOperator { And, Less, Equal };

class ConditionalJump : public Statement {
 public:
  ConditionalJump(LogicalOperator logicalOperator,
                  std::shared_ptr<Expression> expressionLeft,
                  std::shared_ptr<Expression> expressionRight,
                  Address addressIf, Address addressElse);

  void Accept(Visitor* visitor) final;

  std::vector<std::shared_ptr<Expression>> Kids() final;

  std::shared_ptr<Statement> Build(
      const std::vector<std::shared_ptr<Expression>>& expressionList) final;

 public:
  const LogicalOperator logicalOperator_;
  const std::shared_ptr<Expression> expressionLeft_;
  const std::shared_ptr<Expression> expressionRight_;
  const Address addressIf_;
  const Address addressElse_;
};

inline ConditionalJump::ConditionalJump(
    LogicalOperator logicalOperator, std::shared_ptr<Expression> expressionLeft,
    std::shared_ptr<Expression> expressionRight, Address addressIf,
    Address addressElse)
    : logicalOperator_{logicalOperator},
      expressionLeft_{std::move(expressionLeft)},
      expressionRight_{std::move(expressionRight)},
      addressIf_{std::move(addressIf)},
      addressElse_{std::move(addressElse)} {
  assert(expressionLeft_ != nullptr);
  assert(expressionRight_ != nullptr);
}

inline void ConditionalJump::Accept(Visitor* visitor) { visitor->Visit(this); }

inline std::vector<std::shared_ptr<Expression>> ConditionalJump::Kids() {
  return {expressionLeft_, expressionRight_};
}

inline std::shared_ptr<Statement> ConditionalJump::Build(
    const std::vector<std::shared_ptr<Expression>>& expressionList) {
  return std::make_shared<ConditionalJump>(logicalOperator_, expressionList[0],
                                           expressionList[1], addressIf_,
                                           addressElse_);
}

}  // namespace Ct
