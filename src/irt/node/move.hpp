#pragma once

#include <memory>
#include "statement.hpp"

namespace Irt {

class Expression;

class Move : public Statement {
 public:
  Move(std::shared_ptr<Expression> destination,
       std::shared_ptr<Expression> source);

  virtual void Accept(Visitor* visitor) override final;

 public:
  const std::shared_ptr<Expression> destination_;
  const std::shared_ptr<Expression> source_;
};

}  // namespace Irt
