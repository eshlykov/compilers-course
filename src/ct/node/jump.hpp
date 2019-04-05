#pragma once

#include <memory>
#include <vector>
#include "../../utils/address.hpp"
#include "statement.hpp"

namespace Ct {

class Expression;

class Jump : public Statement {
 public:
  explicit Jump(const Address& address);

  virtual void Accept(Visitor* visitor) override final;

  virtual std::vector<std::shared_ptr<Expression>> Kids() override final;

  virtual std::shared_ptr<Statement> Build(
      const std::vector<std::shared_ptr<Expression>>& expressionList)
      override final;

 public:
  const std::shared_ptr<Expression> expression_;
  const std::vector<Address> addresses_;
};

}  // namespace Ct
