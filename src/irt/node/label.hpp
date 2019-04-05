#pragma once

#include <memory>
#include <string>
#include "../../utils/address.hpp"
#include "statement.hpp"

namespace Irt {

class Label : public Statement {
 public:
  explicit Label(const Address& address);

  virtual void Accept(Visitor* visitor) override final;

 public:
  const Address address_;
};

}  // namespace Irt
