#pragma once

#include "expression.hpp"
#include <memory>

namespace Irt {

    class ExpressionSequence : public Expression {
    public:
        ExpressionSequence(std::shared_ptr<Expression> leftExpression,
            std::shared_ptr<Expression> rightExpression);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const std::shared_ptr<Expression> leftExpression_;
        const std::shared_ptr<Expression> rightExpression_;
    };

}
