#pragma once

#include "statement.hpp"
#include <memory>

namespace Ct {

    class Expression;

    class Move : public Statement {
    public:
        Move(std::shared_ptr<Expression> destination,
            std::shared_ptr<Expression> source);

        virtual void Accept(Visitor* visitor) override final;

        virtual std::vector<std::shared_ptr<Expression>> Kids() override final;

        virtual std::shared_ptr<Statement> Build(
            const std::vector<std::shared_ptr<Expression>>& expressionList) override final;

    public:
        const std::shared_ptr<Expression> destination_;
        const std::shared_ptr<Expression> source_;
    };

}
