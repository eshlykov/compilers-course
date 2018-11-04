#pragma once

#include "../visitor.hpp"
#include "expression.hpp"

class BoolExpression : public Expression {
public:
    BoolExpression(bool value) :
        value_{value} {
    }

    virtual void Accept(Visitor* visitor) {
        visitor->Visit(this):
    }

public:
    bool value_ = {};
};
