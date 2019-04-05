#include "user-type-constructor-expression.hpp"

namespace Ast {

    UserTypeConstructorExpression::UserTypeConstructorExpression(Location location,
        const std::string& name) :
            name_{name} {
        SetLocation(location);
    }

    void UserTypeConstructorExpression::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
