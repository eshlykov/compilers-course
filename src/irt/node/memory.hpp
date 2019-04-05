#pragma once

#include <memory>
#include "expression.hpp"

namespace Irt {

class Memory : public Expression {
 public:
  explicit Memory(std::shared_ptr<Expression> expression);

  virtual void Accept(Visitor* visitor) override final;

 public:
  const std::shared_ptr<Expression> expression_;
};

}  // namespace Irt
