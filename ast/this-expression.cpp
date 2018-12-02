#include "this-expression.hpp"

class Type;

ThisExpression::ThisExpression(Location location) {
    SetLocation(location);
}

void ThisExpression::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
