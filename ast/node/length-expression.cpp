#include "length-expression.hpp"

namespace Ast {

    LengthExpression::LengthExpression(Location location,
        std::unique_ptr<Expression> expression) :
            expression_{std::move(expression)} {
        SetLocation(location);
        assert(expression_ != nullptr);
    }

    void LengthExpression::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}