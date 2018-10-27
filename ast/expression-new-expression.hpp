#pragma once

#include "expression.hpp"

class ExpressionNewExpression : public Expression {
public:
    ExpressionNewExpression(Expression* expression) : expression_{expression} {
    }

public:
    Expression* expression_ = {};
};
