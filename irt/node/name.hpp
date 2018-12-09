#pragma once

#include "expression.hpp"
#include <memory>

namespace Irt {

    class Name : public Expression {
    public:
        explicit Name(const Address& label);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const Address label_;
    };

}
