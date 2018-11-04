#pragma once

#include "../visitor.hpp"
#include "expression.hpp"

class LengthExpression : public Expression {
public:
    LengthExpression(Expression* expression) :
        expression_{expression} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Expression* expression_ = {};
};