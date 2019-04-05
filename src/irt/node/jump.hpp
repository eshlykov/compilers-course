#pragma once

#include <memory>
#include <vector>
#include "../../utils/address.hpp"
#include "statement.hpp"

namespace Irt {

class Expression;

class Jump : public Statement {
 public:
  explicit Jump(const Address& address);

  virtual void Accept(Visitor* visitor) override final;

 public:
  const std::shared_ptr<Expression> expression_;
  const std::vector<Address> addresses_;
};

}  // namespace Irt
