#pragma once

#include "expression.hpp"

namespace Ct {

    class Constant : public Expression {
    public:
        explicit Constant(int value);

        virtual void Accept(Visitor* visitor) override final;

        virtual std::vector<std::shared_ptr<Expression>> Kids() override final;

        virtual std::shared_ptr<Expression> Build(
            const std::vector<std::shared_ptr<Expression>>& expressionList) override final;

    public:
        const int value_;
    };

}
