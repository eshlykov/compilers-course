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

  std::vector<ExpressionPtr> Kids() final;

  StatementPtr Build(const std::vector<ExpressionPtr>& expressionList) final;

 public:
  const Address address_;
};

inline Label::Label(Address address) : address_{std::move(address)} {}

inline void Label::Accept(Visitor* visitor) { visitor->Visit(this); }

inline std::vector<ExpressionPtr> Label::Kids() { return {}; }

inline StatementPtr Label::Build(
    const std::vector<ExpressionPtr>& expressionList) {
  return std::make_shared<Label>(address_);
}

using LabelPtr = std::shared_ptr<Label>;

}  // namespace Ct
