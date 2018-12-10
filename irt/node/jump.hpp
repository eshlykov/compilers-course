#pragma once

#include "statement.hpp"
#include <memory>
#include <vector>

namespace Irt {

    class Expression;

    class Jump : public Statement {
    public:
        Jump(std::shared_ptr<Expression> expression,
            const std::vector<Address>& addresses);

        Jump(const Address& address);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const std::shared_ptr<Expression> expression_;
        const std::vector<Address> addresses_;
    };

}
