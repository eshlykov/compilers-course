#pragma once

#include "expression.hpp"
#include <memory>

namespace Ct {

    enum class ArithmeticOperator {
        Plus,
        Minus,
        Multiplication
    };

    class BinaryOperator : public Expression {
    public:
        BinaryOperator(ArithmeticOperator arithmeticOperator,
            std::shared_ptr<Expression> leftExpression,
            std::shared_ptr<Expression> rightExpression);

        virtual void Accept(Visitor* visitor) override final;

        virtual std::vector<std::shared_ptr<Expression>> Kids() override final;

        virtual std::shared_ptr<Expression> Build(
            const std::vector<std::shared_ptr<Expression>>& expressionList) override final;

    public:
        const ArithmeticOperator arithmeticOperator_;
        const std::shared_ptr<Expression> leftExpression_;
        const std::shared_ptr<Expression> rightExpression_;
    };

}
