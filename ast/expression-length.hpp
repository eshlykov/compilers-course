#pragma once

#include "expression.hpp"

class ExpressionLength : public Expression {
public:
    ExpressionLength(Expression* expression) :
        expression_{expression} {
    }

public:
    Expression* expression_ = {};
};
