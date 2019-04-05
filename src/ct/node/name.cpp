#include "name.hpp"

namespace Ct {

Name::Name(const Address& address) : address_{address} {}

void Name::Accept(Visitor* visitor) { visitor->Visit(this); }

std::vector<std::shared_ptr<Expression>> Name::Kids() { return {}; }

std::shared_ptr<Expression> Name::Build(
    const std::vector<std::shared_ptr<Expression>>& expressionList) {
  return std::make_shared<Name>(address_);
}

}  // namespace Ct
