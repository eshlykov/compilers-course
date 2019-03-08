#pragma once

#include "../utils/address.hpp"
#include "statement.hpp"
#include <memory>
#include <vector>

namespace Ct {

    class Expression;

    class Jump : public Statement {
    public:
        explicit Jump(const Address& address);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const std::shared_ptr<Expression> expression_;
        const std::vector<Address> addresses_;
    };

}
