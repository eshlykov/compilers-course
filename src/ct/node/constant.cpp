#include "constant.hpp"

namespace Ct {

Constant::Constant(int value) : value_{value} {}

void Constant::Accept(Visitor* visitor) { visitor->Visit(this); }

std::vector<std::shared_ptr<Expression>> Constant::Kids() { return {}; }

std::shared_ptr<Expression> Constant::Build(
    const std::vector<std::shared_ptr<Expression>>& expressionList) {
  return std::make_shared<Constant>(value_);
}

}  // namespace Ct
