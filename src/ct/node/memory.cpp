#include "memory.hpp"

namespace Ct {

Memory::Memory(std::shared_ptr<Expression> expression)
    : expression_{expression} {
  assert(expression_ != nullptr);
}

void Memory::Accept(Visitor* visitor) { visitor->Visit(this); }

std::vector<std::shared_ptr<Expression>> Memory::Kids() {
  return {expression_};
}

std::shared_ptr<Expression> Memory::Build(
    const std::vector<std::shared_ptr<Expression>>& expressionList) {
  return std::make_shared<Memory>(expressionList[0]);
}

}  // namespace Ct
