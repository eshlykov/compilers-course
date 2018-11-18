#pragma once

#include "../visitor.hpp"
#include "expression.hpp"

class BooleanExpression : public Expression {
public:
    explicit BooleanExpression(Location location,
        bool value) :
            value_{value} {
        location_ = location;
    }

    virtual void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    const bool value_;
};
