#include "user-type-constructor-expression.hpp"

explicit UserTypeConstructorExpression::UserTypeConstructorExpression(Location location,
    const std::string& name) :
        name_{name} {
    location_ = location;
}

virtual void UserTypeConstructorExpression::Accept(Visitor* visitor) override final {
    visitor->Visit(this);
}