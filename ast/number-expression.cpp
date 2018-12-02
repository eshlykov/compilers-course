#include "number-expression.hpp"

NumberExpression::NumberExpression(Location location,
    int value) :
        value_{value} {
    SetLocation(location);
}

void NumberExpression::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
