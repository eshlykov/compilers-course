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

  std::vector<std::shared_ptr<Expression>> Kids() final;

  std::shared_ptr<Statement> Build(
      const std::vector<std::shared_ptr<Expression>>& expressionList) final;

 public:
  const std::shared_ptr<Expression> expression_;
  const std::vector<Address> addresses_;
};

inline Jump::Jump(Address address)
    : expression_{std::make_shared<Name>(address)}, addresses_{std::move(address)} {
  assert(expression_ != nullptr);
}

inline void Jump::Accept(Visitor* visitor) { visitor->Visit(this); }

inline std::vector<std::shared_ptr<Expression>> Jump::Kids() {
  return {expression_};
}

inline std::shared_ptr<Statement> Jump::Build(
    const std::vector<std::shared_ptr<Expression>>& expressionList) {
  assert(!addresses_.empty());
  return std::make_shared<Jump>(addresses_[0]);
}

}  // namespace Ct
