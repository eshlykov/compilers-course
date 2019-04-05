#pragma once

#include "expression.hpp"

namespace Ast {

    class NumberExpression : public Expression {
    public:
        explicit NumberExpression(Location location,
            int value);

        void Accept(Visitor* visitor) final;

    public:
        const int value_;
    };

    inline NumberExpression::NumberExpression(Location location,
        int value) :
        value_{value} {
        SetLocation(location);
    }

    inline void NumberExpression::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
