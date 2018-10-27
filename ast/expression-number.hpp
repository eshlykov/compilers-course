#pragma once

#include "expression.hpp"

class Number;

class ExpressionNumber : public Expression {
public:
    ExpressionNumber(Number* number) : number_{number} {
    }

public:
    Number* number_ = {};
};
