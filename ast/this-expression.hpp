#pragma once

#include "../visitor.hpp"
#include "expression.hpp"

class ThisExpression : public Expression {
public:
    ThisExpression(Location location) {
        location_ = location;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }
};
