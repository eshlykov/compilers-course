#pragma once

#include "expression.hpp"

class ExpressionParentheses : public Expression {
public:
    ExpressionParentheses(Expression* expression) : expression_{expression} {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    Expression* expression_ = {};
};
