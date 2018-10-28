#pragma once

#include "../visitor.hpp"
#include "expression.hpp"

class ExpressionLength : public Expression {
public:
    ExpressionLength(Expression* expression) :
        expression_{expression} {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    Expression* expression_ = {};
};
