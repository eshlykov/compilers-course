#include "conditional-jump.hpp"

namespace Ct {

ConditionalJump::ConditionalJump(LogicalOperator logicalOperator,
                                 std::shared_ptr<Expression> expressionLeft,
                                 std::shared_ptr<Expression> expressionRight,
                                 const Address& addressIf,
                                 const Address& addressElse)
    : logicalOperator_{logicalOperator},
      expressionLeft_{expressionLeft},
      expressionRight_{expressionRight},
      addressIf_{addressIf},
      addressElse_{addressElse} {
  assert(expressionLeft_ != nullptr);
  assert(expressionRight_ != nullptr);
}

void ConditionalJump::Accept(Visitor* visitor) { visitor->Visit(this); }

std::vector<std::shared_ptr<Expression>> ConditionalJump::Kids() {
  return {expressionLeft_, expressionRight_};
}

std::shared_ptr<Statement> ConditionalJump::Build(
    const std::vector<std::shared_ptr<Expression>>& expressionList) {
  return std::make_shared<ConditionalJump>(logicalOperator_, expressionList[0],
                                           expressionList[1], addressIf_,
                                           addressElse_);
}

}  // namespace Ct
