#include "number-expression.hpp"

namespace Ast {

    NumberExpression::NumberExpression(Location location,
        int value) :
            value_{value} {
        SetLocation(location);
    }

    void NumberExpression::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
