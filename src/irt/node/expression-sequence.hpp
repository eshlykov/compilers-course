#pragma once

#include <memory>
#include "expression.hpp"

namespace Irt {

class Statement;

class ExpressionSequence : public Expression {
 public:
  ExpressionSequence(std::shared_ptr<Statement> statement,
                     std::shared_ptr<Expression> expression);

  virtual void Accept(Visitor* visitor) override final;

 public:
  const std::shared_ptr<Statement> statement_;
  const std::shared_ptr<Expression> expression_;
};

}  // namespace Irt
