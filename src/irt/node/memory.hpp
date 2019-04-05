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

inline Memory::Memory(std::shared_ptr<Expression> expression)
    : expression_{expression} {
  assert(expression_ != nullptr);
}

inline void Memory::Accept(Visitor* visitor) { visitor->Visit(this); }

}  // namespace Irt
