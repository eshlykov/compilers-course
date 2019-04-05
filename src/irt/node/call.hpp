#pragma once

#include <memory>
#include <vector>
#include "expression.hpp"

namespace Irt {

class Call : public Expression {
 public:
  Call(std::shared_ptr<Expression> expression,
       std::vector<std::shared_ptr<Expression>> expressionList);

  void Accept(Visitor* visitor) final;

 public:
  const std::shared_ptr<Expression> expression_;
  const std::vector<std::shared_ptr<Expression>> expressionList_;
};

inline Call::Call(std::shared_ptr<Expression> expression,
                  std::vector<std::shared_ptr<Expression>> expressionList)
    : expression_(std::move(expression)),
      expressionList_(std::move(expressionList)) {
  assert(expression_ != nullptr);
}

inline void Call::Accept(Visitor* visitor) { visitor->Visit(this); }

}  // namespace Irt
