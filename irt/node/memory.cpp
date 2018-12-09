#include "memory.hpp"

Memory::Memory(std::shared_ptr<Expression> expression) :
    expression_{expression} {
}

void Memory::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
