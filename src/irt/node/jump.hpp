#pragma once

#include <memory>
#include <vector>
#include "../../utils/address.hpp"
#include "name.hpp"
#include "statement.hpp"

namespace Irt {

class Expression;

class Jump : public Statement {
 public:
  explicit Jump(const Address& address);

  void Accept(Visitor* visitor) final;

 public:
  const std::shared_ptr<Expression> expression_;
  const std::vector<Address> addresses_;
};

inline Jump::Jump(const Address& address)
    : expression_{std::make_shared<Name>(address)}, addresses_{address} {
  assert(expression_ != nullptr);
}

inline void Jump::Accept(Visitor* visitor) { visitor->Visit(this); }

}  // namespace Irt
