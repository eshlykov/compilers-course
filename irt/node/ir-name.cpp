#include "ir-name.hpp"

IrName::IrName(std::shared_ptr<IrLabel> label) :
    label_{label} {
}

void IrName::Accept(IrVisitor* visitor) {
    visitor->Visit(this);
}
