#pragma once

#include <memory>
#include "../../utils/address.hpp"
#include "expression.hpp"

namespace Ct {

class Name : public Expression {
 public:
  explicit Name(const Address& address);

  virtual void Accept(Visitor* visitor) override final;

  virtual std::vector<std::shared_ptr<Expression>> Kids() override final;

  virtual std::shared_ptr<Expression> Build(
      const std::vector<std::shared_ptr<Expression>>& expressionList)
      override final;

 public:
  const Address address_;
};

inline Name::Name(const Address& address) : address_{address} {}

inline void Name::Accept(Visitor* visitor) { visitor->Visit(this); }

inline std::vector<std::shared_ptr<Expression>> Name::Kids() { return {}; }

inline std::shared_ptr<Expression> Name::Build(
    const std::vector<std::shared_ptr<Expression>>& expressionList) {
  return std::make_shared<Name>(address_);
}

}  // namespace Ct
