#pragma once

#include "../visitor.hpp"
#include "expression.hpp"

class BooleanExpression : public Expression {
public:
    explicit BooleanExpression(bool value) :
        value_{value} {
    }

    virtual void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    bool value_ = {};
};
