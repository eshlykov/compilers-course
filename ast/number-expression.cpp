#include "number-expression.hpp"

NumberExpression::NumberExpression(Location location,
    int value) :
        value_{value} {
    location_ = location;
}

void NumberExpression::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
