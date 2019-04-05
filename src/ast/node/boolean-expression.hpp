#pragma once

#include "expression.hpp"

namespace Ast {

    class BooleanExpression : public Expression {
    public:
        explicit BooleanExpression(Location location,
            bool value);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const bool value_;
    };

}
