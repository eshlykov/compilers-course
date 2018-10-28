#pragma once

class Expression;

class CommaExpression {
public:
    CommaExpression(Expression* expression) :
        expression_{expression} {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    Expression* expression_ = {};
};
