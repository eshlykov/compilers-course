#pragma once

#include "expression.hpp"

class ExpressionBang : public Expression {
public:
    ExpressionBang(Expression* expression) : expression_{expression} {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    Expression* expression_ = {};
};
