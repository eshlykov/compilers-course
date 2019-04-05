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
                  const Address& addressIf, const Address& addressElse);

  virtual void Accept(Visitor* visitor) override final;

  virtual std::vector<std::shared_ptr<Expression>> Kids() override final;

  virtual std::shared_ptr<Statement> Build(
      const std::vector<std::shared_ptr<Expression>>& expressionList)
      override final;

 public:
  const LogicalOperator logicalOperator_;
  const std::shared_ptr<Expression> expressionLeft_;
  const std::shared_ptr<Expression> expressionRight_;
  const Address addressIf_;
  const Address addressElse_;
};

}  // namespace Ct
