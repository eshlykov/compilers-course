#pragma once

#include "expression.hpp"

class ExpressionAtExpression : public Expression {
public:
    ExpressionAtExpression(Expression* lhs, Expression* rhs) :
        lhs_{lhs}, rhs_{rhs} {
    }

public:
    Expression* lhs_ = {};
    Expression* rhs_ = {};
};
