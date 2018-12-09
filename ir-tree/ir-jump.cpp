#include "ir-jump.hpp"

IrJump::IrJump(std::shared_ptr<IrExpression> expression,
    const std::vector<std::shared_ptr<IrLabel>>& labels) :
        expression_{expression},
        labels_{labels} {
    assert(expression_ != nullptr);
}

void IrJump::Accept(IrVisitor* visitor) {
    visitor->Visit(this);
}
