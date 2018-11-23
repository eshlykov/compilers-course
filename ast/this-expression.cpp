#include "this-expression.hpp"

ThisExpression::ThisExpression(Location location) {
    location_ = location;
}

void ThisExpression::Accept(Visitor* visitor) {
    visitor->Visit(this);
}