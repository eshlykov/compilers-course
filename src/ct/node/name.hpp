#pragma once

#include <memory>
#include "../../utils/address.hpp"
#include "expression.hpp"

namespace Ct {

class Name : public Expression {
 public:
  explicit Name(Address address);

  void Accept(Visitor* visitor) final;

  std::vector<ExpressionPtr> Kids() final;

  ExpressionPtr Build(const std::vector<ExpressionPtr>& expressionList) final;

 public:
  const Address address_;
};

inline Name::Name(Address address) : address_{std::move(address)} {}

inline void Name::Accept(Visitor* visitor) { visitor->Visit(this); }

inline std::vector<ExpressionPtr> Name::Kids() { return {}; }

inline ExpressionPtr Name::Build(
    const std::vector<ExpressionPtr>& expressionList) {
  return std::make_shared<Name>(address_);
}

using NamePtr = std::shared_ptr<Name>;

}  // namespace Ct
