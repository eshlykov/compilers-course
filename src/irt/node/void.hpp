#pragma once

#include <memory>
#include "statement.hpp"

namespace Irt {

class Expression;

class Void : public Statement {
 public:
  explicit Void(std::shared_ptr<Expression> expression);

  virtual void Accept(Visitor* visitor) override final;

 public:
  const std::shared_ptr<Expression> expression_;
};

}  // namespace Irt
