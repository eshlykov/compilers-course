#include "ir-label.hpp"

IrLabel::IrLabel(const std::string& label) :
    label_{label} {
}

void IrLabel::Accept(IrVisitor* visitor) {
    visitor->Visit(this);
}
