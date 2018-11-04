#pragma once

#include "../visitor.hpp"
#include "expression.hpp"

class NotExpression : public Expression {
public:
    NotExpression(Expression* expression) :
        expression_{expression} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Expression* expression_ = {};
};
