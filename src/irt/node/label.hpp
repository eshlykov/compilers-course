#pragma once

#include <memory>
#include <string>
#include "../../utils/address.hpp"
#include "statement.hpp"

namespace Irt {

class Label : public Statement {
 public:
  explicit Label(Address address);

  void Accept(Visitor* visitor) final;

 public:
  const Address address_;
};

inline Label::Label(Address address) : address_{std::move(address)} {}

inline void Label::Accept(Visitor* visitor) { visitor->Visit(this); }

}  // namespace Irt
