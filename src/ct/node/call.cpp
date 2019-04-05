#include "call.hpp"

namespace Ct {

Call::Call(std::shared_ptr<Expression> expression,
           const std::vector<std::shared_ptr<Expression>>& expressionList)
    : expression_(expression), expressionList_(expressionList) {
  assert(expression_ != nullptr);
}

void Call::Accept(Visitor* visitor) { visitor->Visit(this); }

std::vector<std::shared_ptr<Expression>> Call::Kids() {
  std::vector<std::shared_ptr<Expression>> newVec(expressionList_.begin(),
                                                  expressionList_.end());
  newVec.insert(newVec.begin(), expression_);
  return newVec;
}

std::shared_ptr<Expression> Call::Build(
    const std::vector<std::shared_ptr<Expression>>& expressionList) {
  std::vector<std::shared_ptr<Expression>> newVec(expressionList.begin() + 1,
                                                  expressionList.end());
  return std::make_shared<Call>(expressionList[0], newVec);
}

}  // namespace Ct
