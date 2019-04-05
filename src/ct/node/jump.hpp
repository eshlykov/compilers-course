#pragma once

#include <memory>
#include <vector>
#include "../../utils/address.hpp"
#include "name.hpp"
#include "statement.hpp"

namespace Ct {

class Expression;

class Jump : public Statement {
 public:
  explicit Jump(Address address);

  void Accept(Visitor* visitor) final;

  std::vector<ExpressionPtr> Kids() final;

  StatementPtr Build(const std::vector<ExpressionPtr>& expressionList) final;

 public:
  const ExpressionPtr expression_;
  const Address address_;
};

inline Jump::Jump(Address address)
    : expression_{std::make_shared<Name>(address)},
      address_{std::move(address)} {
  assert(expression_ != nullptr);
}

inline void Jump::Accept(Visitor* visitor) { visitor->Visit(this); }

inline std::vector<ExpressionPtr> Jump::Kids() { return {expression_}; }

inline StatementPtr Jump::Build(
    const std::vector<ExpressionPtr>& expressionList) {
  return std::make_shared<Jump>(address_);
}

using JumpPtr = std::shared_ptr<Jump>;

}  // namespace Ct
