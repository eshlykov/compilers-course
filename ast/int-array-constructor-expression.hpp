#pragma once

#include "../visitor.hpp"
#include "expression.hpp"

class IntArrayConstructorExpression : public Expression {
public:
    explicit IntArrayConstructorExpression(Expression* expression) :
        expression_{expression} {
    }

    ~IntArrayConstructorExpression() {
        delete expression_;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Expression* expression_ = {};
};
