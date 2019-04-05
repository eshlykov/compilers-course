#pragma once

#include <memory>
#include "../../utils/address.hpp"
#include "statement.hpp"

namespace Irt {

class Expression;

enum class LogicalOperator { And, Less, Equal };

class ConditionalJump : public Statement {
 public:
  ConditionalJump(LogicalOperator logicalOperator,
                  std::shared_ptr<Expression> expressionLeft,
                  std::shared_ptr<Expression> expressionRight,
                  Address addressIf, Address addressElse);

  void Accept(Visitor* visitor) final;

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

}  // namespace Irt
