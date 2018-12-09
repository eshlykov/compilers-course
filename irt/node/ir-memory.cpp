#include "ir-memory.hpp"

IrMemory::IrMemory(std::shared_ptr<IrExpression> expression) :
    expression_{expression} {
}

void IrMemory::Accept(IrVisitor* visitor) {
    visitor->Visit(this);
}
