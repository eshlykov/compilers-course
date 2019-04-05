#include "jump.hpp"
#include "name.hpp"

namespace Ct {

Jump::Jump(const Address& address)
    : expression_{std::make_shared<Name>(address)}, addresses_{address} {
  assert(expression_ != nullptr);
}

void Jump::Accept(Visitor* visitor) { visitor->Visit(this); }

std::vector<std::shared_ptr<Expression>> Jump::Kids() { return {expression_}; }

std::shared_ptr<Statement> Jump::Build(
    const std::vector<std::shared_ptr<Expression>>& expressionList) {
  assert(!addresses_.empty());
  return std::make_shared<Jump>(addresses_[0]);
}

}  // namespace Ct
