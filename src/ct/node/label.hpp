#pragma once

#include <memory>
#include <string>
#include "../../utils/address.hpp"
#include "statement.hpp"

namespace Ct {

class Label : public Statement {
 public:
  explicit Label(Address address);

  void Accept(Visitor* visitor) final;

  std::vector<std::shared_ptr<Expression>> Kids() final;

  std::shared_ptr<Statement> Build(
      const std::vector<std::shared_ptr<Expression>>& expressionList) final;

 public:
  const Address address_;
};

inline Label::Label(Address address) : address_{std::move(address)} {}

inline void Label::Accept(Visitor* visitor) { visitor->Visit(this); }

inline std::vector<std::shared_ptr<Expression>> Label::Kids() { return {}; }

inline std::shared_ptr<Statement> Label::Build(
    const std::vector<std::shared_ptr<Expression>>& expressionList) {
  return std::make_shared<Label>(address_);
}

}  // namespace Ct
