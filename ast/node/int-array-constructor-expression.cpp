#include "int-array-constructor-expression.hpp"

namespace Ast {

    IntArrayConstructorExpression::IntArrayConstructorExpression(Location location,
        std::unique_ptr<Expression> expression) :
            expression_{std::move(expression)} {
        SetLocation(location);
        assert(expression_ != nullptr);
    }

    void IntArrayConstructorExpression::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
