#include "not-expression.hpp"

NotExpression::NotExpression(Location location,
    std::unique_ptr<Expression> expression) :
        expression_{std::move(expression)} {
    location_ = location;
}

void NotExpression::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
