#pragma once

#include "statement.hpp"
#include <memory>
#include <vector>

namespace Irt {

    class Expression;
    class Label;

    class Jump : public Statement {
    public:
        Jump(std::shared_ptr<Expression> expression,
            const std::vector<std::shared_ptr<Label>>& labels);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const std::shared_ptr<Expression> expression_;
        const std::vector<std::shared_ptr<Label>> labels_;
    };

}
