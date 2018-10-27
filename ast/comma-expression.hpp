#pragma once

class Expression;

class CommaExpression {
public:
    CommaExpression(Expression* expression) :
        expression_{expression} {
    }

public:
    Expression* expression_ = {};
};
