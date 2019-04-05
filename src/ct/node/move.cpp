#include "move.hpp"
#include "memory.hpp"

namespace Ct {

Move::Move(std::shared_ptr<Expression> destination,
           std::shared_ptr<Expression> source)
    : destination_{destination}, source_{source} {
  assert(destination_ != nullptr);
  assert(source_ != nullptr);
}

void Move::Accept(Visitor* visitor) { visitor->Visit(this); }

std::vector<std::shared_ptr<Expression>> Move::Kids() {
  if (std::dynamic_pointer_cast<Memory>(destination_) != nullptr) {
    return {std::dynamic_pointer_cast<Memory>(destination_), source_};
  } else {
    return {source_};
  }
}

std::shared_ptr<Statement> Move::Build(
    const std::vector<std::shared_ptr<Expression>>& expressionList) {
  if (std::dynamic_pointer_cast<Memory>(destination_) != nullptr) {
    return std::make_shared<Move>(std::make_shared<Memory>(expressionList[0]),
                                  expressionList[1]);
  } else {
    return std::make_shared<Move>(destination_, expressionList[0]);
  }
}

}  // namespace Ct
