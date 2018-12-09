#pragma once

#include "expression.hpp"
#include <memory>

namespace Ast {

    enum class BinaryOperator {
        And,
        Less,
        Plus,
        Minus,
        Star,
    };

    class BinaryOperatorExpression : public Expression {
    public:
        BinaryOperatorExpression(Location location,
            std::unique_ptr<Expression> lhs,
            std::unique_ptr<Expression> rhs,
            BinaryOperator binaryOperator);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const std::unique_ptr<Expression> lhs_;
        const std::unique_ptr<Expression> rhs_;
        const BinaryOperator binaryOperator_;
    };

}
