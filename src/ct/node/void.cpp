#include "void.hpp"

namespace Ct {

Void::Void(std::shared_ptr<Expression> expression) : expression_{expression} {
  assert(expression_ != nullptr);
}

void Void::Accept(Visitor* visitor) { visitor->Visit(this); }

std::vector<std::shared_ptr<Expression>> Void::Kids() { return {expression_}; }

std::shared_ptr<Statement> Void::Build(
    const std::vector<std::shared_ptr<Expression>>& expressionList) {
  return std::make_shared<Void>(expressionList[0]);
}

}  // namespace Ct
