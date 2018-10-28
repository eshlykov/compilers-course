#pragma once

#include "expression.hpp"

class ExpressionAtExpression : public Expression {
public:
    ExpressionAtExpression(Expression* lhs, Expression* rhs) :
        lhs_{lhs}, rhs_{rhs} {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    Expression* lhs_ = {};
    Expression* rhs_ = {};
};
