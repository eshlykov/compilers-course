#include "constant.hpp"

Constant::Constant(int value) :
    value_{value} {
}

void Constant::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
