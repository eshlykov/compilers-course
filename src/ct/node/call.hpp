#pragma once

#include <memory>
#include <vector>
#include "expression.hpp"

namespace Ct {

class Call : public Expression {
 public:
  Call(std::shared_ptr<Expression> expression,
       const std::vector<std::shared_ptr<Expression>>& expressionList);

  void Accept(Visitor* visitor) final;

  std::vector<std::shared_ptr<Expression>> Kids() final;

  std::shared_ptr<Expression> Build(
      const std::vector<std::shared_ptr<Expression>>& expressionList) final;

 public:
  const std::shared_ptr<Expression> expression_;
  const std::vector<std::shared_ptr<Expression>> expressionList_;
};

inline Call::Call(
    std::shared_ptr<Expression> expression,
    const std::vector<std::shared_ptr<Expression>>& expressionList)
    : expression_(expression), expressionList_(expressionList) {
  assert(expression_ != nullptr);
}

inline void Call::Accept(Visitor* visitor) { visitor->Visit(this); }

inline std::vector<std::shared_ptr<Expression>> Call::Kids() {
  std::vector<std::shared_ptr<Expression>> newVec(expressionList_.begin(),
                                                  expressionList_.end());
  newVec.insert(newVec.begin(), expression_);
  return newVec;
}

inline std::shared_ptr<Expression> Call::Build(
    const std::vector<std::shared_ptr<Expression>>& expressionList) {
  std::vector<std::shared_ptr<Expression>> newVec(expressionList.begin() + 1,
                                                  expressionList.end());
  return std::make_shared<Call>(expressionList[0], newVec);
}

}  // namespace Ct
