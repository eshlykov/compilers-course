#pragma once

#include <memory>
#include "statement.hpp"

namespace Ct {

class Expression;

class Void : public Statement {
 public:
  explicit Void(std::shared_ptr<Expression> expression);

  virtual void Accept(Visitor* visitor) override final;

  virtual std::vector<std::shared_ptr<Expression>> Kids() override final;

  virtual std::shared_ptr<Statement> Build(
      const std::vector<std::shared_ptr<Expression>>& expressionList)
      override final;

 public:
  const std::shared_ptr<Expression> expression_;
};

}  // namespace Ct
