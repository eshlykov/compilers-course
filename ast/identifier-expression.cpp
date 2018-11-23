#include "identifier-expression.hpp"

IdentifierExpression::IdentifierExpression(Location location,
    const std::string& name) :
        name_{name} {
    location_ = location;
}

void IdentifierExpression::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
