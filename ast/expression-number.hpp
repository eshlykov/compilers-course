#pragma once

#include "expression.hpp"

class Number;

class ExpressionNumber : public Expression {
public:
    ExpressionNumber(Number* number) : number_{number} {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    Number* number_ = {};
};
