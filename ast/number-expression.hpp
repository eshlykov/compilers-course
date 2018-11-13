#pragma once

#include "../visitor.hpp"
#include "expression.hpp"

class NumberExpression : public Expression {
public:
    explicit NumberExpression(int value) :
        value_{value} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    int value_ = {};
};
