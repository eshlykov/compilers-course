#pragma once

#include "../visitor.hpp"
#include "expression.hpp"

enum class BinaryOperator {
    BO_And,
    BO_Less,
    BO_Plus,
    BO_Minus,
    BO_Star,
};

class BinaryOperatorExpression : public Expression {
public:
    BinaryOperatorExpression(Expression* lhs,
        Expression* rhs,
        BinaryOperator binaryOperator) :
            lhs_{lhs},
            rhs_{rhs},
            binaryOperator_{binaryOperator} {
    }

    ~BinaryOperatorExpression() {
        delete lhs_;
        delete rhs_;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Expression* lhs_;
    Expression* rhs_;
    const BinaryOperator binaryOperator_;
};
