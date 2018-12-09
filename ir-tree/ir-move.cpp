#include "ir-move.hpp"

IrMove::IrMove(std::shared_ptr<IrExpression> destination, std::shared_ptr<IrExpression> source) :
    destination_{destination},
    source_{source} {
}

void IrMove::Accept(IrVisitor* visitor) {
    visitor->Visit(this);
}
