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

class ExpressionBinaryOperatorExpression : public Expression {
public:
    ExpressionBinaryOperatorExpression(Expression* lhs,
        Expression* rhs, BinaryOperator binaryOperator) :
            lhs_{lhs}, rhs_{rhs}, binaryOperator_{binaryOperator} {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    Expression* lhs_ = {};
    Expression* rhs_ = {};
    BinaryOperator binaryOperator_ = {};
};
