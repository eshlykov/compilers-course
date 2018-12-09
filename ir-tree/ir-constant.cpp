#include "ir-constant.hpp"

IrConstant::IrConstant(int value) :
    value_(value) {
}

void IrConstant::Accept(IrVisitor *visitor) {
    visitor->Visit(this);
}
