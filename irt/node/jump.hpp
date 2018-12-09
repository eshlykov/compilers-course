#pragma once

#include "statement.hpp"
#include <memory>
#include <vector>

namespace Irt {

    class Expression;

    class Jump : public Statement {
    public:
        Jump(std::shared_ptr<Expression> expression,
            const std::vector<Address>& labels);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const std::shared_ptr<Expression> expression_;
        const std::vector<Address> labels_;
    };

}
