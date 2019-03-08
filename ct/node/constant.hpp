#pragma once

#include "expression.hpp"

namespace Ct {

    class Constant : public Expression {
    public:
        explicit Constant(int value);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const int value_;
    };

}
