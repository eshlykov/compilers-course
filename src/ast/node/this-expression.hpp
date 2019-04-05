#pragma once

#include "expression.hpp"

namespace Ast {

    class ThisExpression : public Expression {
    public:
        explicit ThisExpression(Location location);

        void Accept(Visitor* visitor) final;
    };

    inline ThisExpression::ThisExpression(Location location) {
        SetLocation(location);
    }

    inline void ThisExpression::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
