#pragma once

#include "expression.hpp"
#include <memory>
#include <vector>

namespace Ct {

    class Call : public Expression {
    public:
        Call(std::shared_ptr<Expression> expression,
            const std::vector<std::shared_ptr<Expression>>& expressionList);

        virtual void Accept(Visitor* visitor) override final;

        virtual std::vector<std::shared_ptr<Expression>> Kids() override final;

        virtual std::shared_ptr<Expression> Build(
            const std::vector<std::shared_ptr<Expression>>& expressionList) override final;

    public:
        const std::shared_ptr<Expression> expression_;
        const std::vector<std::shared_ptr<Expression>> expressionList_;
    };

}
