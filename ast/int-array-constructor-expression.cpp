#include "int-array-constructor-expression.hpp"

IntArrayConstructorExpression::IntArrayConstructorExpression(Location location,
    std::unique_ptr<Expression> expression) :
        expression_{std::move(expression)} {
    SetLocation(location);
}

void IntArrayConstructorExpression::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
