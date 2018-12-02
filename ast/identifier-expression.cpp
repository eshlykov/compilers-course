#include "identifier-expression.hpp"

IdentifierExpression::IdentifierExpression(Location location,
    const std::string& name) :
        name_{name} {
    SetLocation(location);
}

void IdentifierExpression::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
