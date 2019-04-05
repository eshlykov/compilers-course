#pragma once

#include <memory>
#include "expression.hpp"

namespace Ct {

class Memory : public Expression {
 public:
  explicit Memory(std::shared_ptr<Expression> expression);

  virtual void Accept(Visitor* visitor) override final;

  virtual std::vector<std::shared_ptr<Expression>> Kids() override final;

  virtual std::shared_ptr<Expression> Build(
      const std::vector<std::shared_ptr<Expression>>& expressionList)
      override final;

 public:
  const std::shared_ptr<Expression> expression_;
};

}  // namespace Ct
