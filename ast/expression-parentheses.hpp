#pragma once

#include "expression.hpp"

class ExpressionParentheses : public Expression {
public:
    ExpressionParentheses(Expression* expression) : expression_{expression} {
    }

public:
    Expression* expression_ = {};
};
