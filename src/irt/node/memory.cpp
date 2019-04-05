#include "memory.hpp"

namespace Irt {

Memory::Memory(std::shared_ptr<Expression> expression)
    : expression_{expression} {
  assert(expression_ != nullptr);
}

void Memory::Accept(Visitor* visitor) { visitor->Visit(this); }

}  // namespace Irt
