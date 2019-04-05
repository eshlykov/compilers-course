#include "temporary.hpp"

namespace Ct {

Temporary::Temporary(Storage storage) : storage_(storage) {}

void Temporary::Accept(Visitor* visitor) { visitor->Visit(this); }

std::vector<std::shared_ptr<Expression>> Temporary::Kids() { return {}; }

std::shared_ptr<Expression> Temporary::Build(
    const std::vector<std::shared_ptr<Expression>>& expressionList) {
  return std::make_shared<Temporary>(storage_);
}

}  // namespace Ct
