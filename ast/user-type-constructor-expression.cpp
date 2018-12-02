#include "user-type-constructor-expression.hpp"

UserTypeConstructorExpression::UserTypeConstructorExpression(Location location,
    const std::string& name) :
        name_{name} {
    SetLocation(location);
}

void UserTypeConstructorExpression::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
