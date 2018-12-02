#include "boolean-expression.hpp"

BooleanExpression::BooleanExpression(Location location,
    bool value) :
        value_{value} {
    SetLocation(location);
}

void BooleanExpression::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
