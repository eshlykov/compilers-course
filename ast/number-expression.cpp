#include "number-expression.hpp"

NumberExpression::NumberExpression(Location location,
    int value) :
        value_{value} {
    location_ = location;
}

void NumverExpression::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
