#include "length-expression.hpp"

LengthExpression::LengthExpression(Location location,
    std::unique_ptr<Expression> expression) :
        expression_{std::move(expression)} {
    location_ = location;
}

void LengthExpression::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
