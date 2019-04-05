#include "label.hpp"

namespace Ct {

Label::Label(const Address& address) : address_{address} {}

void Label::Accept(Visitor* visitor) { visitor->Visit(this); }

std::vector<std::shared_ptr<Expression>> Label::Kids() { return {}; }

std::shared_ptr<Statement> Label::Build(
    const std::vector<std::shared_ptr<Expression>>& expressionList) {
  return std::make_shared<Label>(address_);
}

}  // namespace Ct
