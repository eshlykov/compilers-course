#pragma once

#include "../visitor.hpp"
#include "expression.hpp"

class ParensExpression : public Expression {
public:
    ParensExpression(Expression* expression) :
        expression_{expression} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Expression* expression_ = {};
};
