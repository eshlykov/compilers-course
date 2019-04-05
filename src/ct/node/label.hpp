#pragma once

#include <memory>
#include <string>
#include "../../utils/address.hpp"
#include "statement.hpp"

namespace Ct {

class Label : public Statement {
 public:
  explicit Label(const Address& address);

  virtual void Accept(Visitor* visitor) override final;

  virtual std::vector<std::shared_ptr<Expression>> Kids() override final;

  virtual std::shared_ptr<Statement> Build(
      const std::vector<std::shared_ptr<Expression>>& expressionList)
      override final;

 public:
  const Address address_;
};

inline Label::Label(const Address& address) : address_{address} {}

inline void Label::Accept(Visitor* visitor) { visitor->Visit(this); }

inline std::vector<std::shared_ptr<Expression>> Label::Kids() { return {}; }

inline std::shared_ptr<Statement> Label::Build(
    const std::vector<std::shared_ptr<Expression>>& expressionList) {
  return std::make_shared<Label>(address_);
}

}  // namespace Ct
