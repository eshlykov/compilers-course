#include "not-expression.hpp"

NotExpression::NotExpression(Location location,
    std::unique_ptr<Expression> expression) :
        expression_{std::move(expression)} {
    SetLocation(location);
    assert(expression_ != nullptr);
}

void NotExpression::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
