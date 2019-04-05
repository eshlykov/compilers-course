#pragma once

#include <memory>
#include "statement.hpp"

namespace Irt {

class Expression;

class Void : public Statement {
 public:
  explicit Void(std::shared_ptr<Expression> expression);

  void Accept(Visitor* visitor) final;

 public:
  const std::shared_ptr<Expression> expression_;
};

inline Void::Void(std::shared_ptr<Expression> expression)
    : expression_{expression} {
  assert(expression_ != nullptr);
}

inline void Void::Accept(Visitor* visitor) { visitor->Visit(this); }

}  // namespace Irt
