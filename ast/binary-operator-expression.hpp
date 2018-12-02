#pragma once

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
