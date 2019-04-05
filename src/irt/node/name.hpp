#pragma once

#include <memory>
#include "../../utils/address.hpp"
#include "expression.hpp"

namespace Irt {

class Name : public Expression {
 public:
  explicit Name(Address address);

  void Accept(Visitor *visitor) final;

 public:
  const Address address_;
};

inline Name::Name(Address address) : address_{std::move(address)} {}

inline void Name::Accept(Visitor *visitor) { visitor->Visit(this); }

}  // namespace Irt
