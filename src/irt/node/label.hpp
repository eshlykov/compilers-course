#pragma once

#include "../utils/address.hpp"
#include "statement.hpp"
#include <memory>
#include <string>

namespace Irt {

    class Label : public Statement {
    public:
        explicit Label(const Address& address);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const Address address_;
    };

}
