#pragma once

#include "expression.hpp"

class NumberExpression : public Expression {
public:
    explicit NumberExpression(Location location,
        int value) :
            value_{value} {
        location_ = location;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    const int value_;
};
