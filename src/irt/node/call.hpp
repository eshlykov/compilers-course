#pragma once

#include <memory>
#include <vector>
#include "expression.hpp"

namespace Irt {

class Call : public Expression {
 public:
  Call(std::shared_ptr<Expression> expression,
       const std::vector<std::shared_ptr<Expression>>& expressionList);

  virtual void Accept(Visitor* visitor) override final;

 public:
  const std::shared_ptr<Expression> expression_;
  const std::vector<std::shared_ptr<Expression>> expressionList_;
};

}  // namespace Irt
