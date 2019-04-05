#pragma once

#include "../utils/address.hpp"
#include "expression.hpp"
#include <memory>

namespace Irt {

    class Name : public Expression {
    public:
        explicit Name(const Address& address);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const Address address_;
    };

}
