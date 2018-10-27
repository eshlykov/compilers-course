#pragma once

#include "expression.hpp"

class ExpressionBang : public Expression {
public:
    ExpressionBang(Expression* expression) : expression_{expression} {
    }

public:
    Expression* expression_ = {};
};
