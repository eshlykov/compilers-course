#pragma once

#include "expression.hpp"
#include <memory>

namespace Ct {

    class Statement;

    class ExpressionSequence : public Expression {
    public:
        ExpressionSequence(std::shared_ptr<Statement> statement,
            std::shared_ptr<Expression> expression);

        virtual void Accept(Visitor* visitor) override final;

        virtual std::vector<std::shared_ptr<Expression>> Kids() override final;

        virtual std::shared_ptr<Expression> Build(
            const std::vector<std::shared_ptr<Expression>>& expressionList) override final;

    public:
        const std::shared_ptr<Statement> statement_;
        const std::shared_ptr<Expression> expression_;
    };

}
