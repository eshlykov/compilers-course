#pragma once

#include <memory>
#include <string>
#include "../utils/address.hpp"
#include "statement.hpp"

namespace Ct {

class Label : public Statement {
 public:
  explicit Label(const Address& address);

  virtual void Accept(Visitor* visitor) override final;

  virtual std::vector<std::shared_ptr<Expression>> Kids() override final;

  virtual std::shared_ptr<Statement> Build(
      const std::vector<std::shared_ptr<Expression>>& expressionList)
      override final;

 public:
  const Address address_;
};

}  // namespace Ct
