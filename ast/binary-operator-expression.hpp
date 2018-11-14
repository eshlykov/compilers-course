#pragma once

#include "../visitor.hpp"
#include "expression.hpp"
#include <memory>

enum class BinaryOperator {
    BO_And,
    BO_Less,
    BO_Plus,
    BO_Minus,
    BO_Star,
};

class BinaryOperatorExpression : public Expression {
public:
    BinaryOperatorExpression(std::unique_ptr<Expression> lhs,
        std::unique_ptr<Expression> rhs,
        BinaryOperator binaryOperator) :
            lhs_{std::move(lhs)},
            rhs_{std::move(rhs)},
            binaryOperator_{binaryOperator} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::unique_ptr<Expression> lhs_;
    std::unique_ptr<Expression> rhs_;
    const BinaryOperator binaryOperator_;
};
