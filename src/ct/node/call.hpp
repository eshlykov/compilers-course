#pragma once

#include <memory>
#include <vector>
#include "expression.hpp"

namespace Ct {

class Call : public Expression {
 public:
  Call(ExpressionPtr expression, std::vector<ExpressionPtr> expressionList);

  void Accept(Visitor* visitor) final;

  std::vector<ExpressionPtr> Kids() final;

  ExpressionPtr Build(const std::vector<ExpressionPtr>& expressionList) final;

 public:
  const ExpressionPtr expression_;
  const std::vector<ExpressionPtr> expressionList_;
};

inline Call::Call(ExpressionPtr expression,
                  std::vector<ExpressionPtr> expressionList)
    : expression_(std::move(expression)),
      expressionList_(std::move(expressionList)) {
  assert(expression_ != nullptr);
}

inline void Call::Accept(Visitor* visitor) { visitor->Visit(this); }

inline std::vector<ExpressionPtr> Call::Kids() {
  std::vector<ExpressionPtr> newVec(expressionList_.begin(),
                                    expressionList_.end());
  newVec.insert(newVec.begin(), expression_);
  return newVec;
}

inline ExpressionPtr Call::Build(
    const std::vector<ExpressionPtr>& expressionList) {
  std::vector<ExpressionPtr> newVec(expressionList.begin() + 1,
                                    expressionList.end());
  return std::make_shared<Call>(expressionList[0], newVec);
}

using CallPtr = std::shared_ptr<Call>;

}  // namespace Ct
