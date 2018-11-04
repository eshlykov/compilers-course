#pragma once

#include "../visitor.hpp"
#include "expression.hpp"

class ThisExpression : public Expression {
public:
    ThisExpression() = default();

    virtual void Accept(Visitor* visitor) override final {
        vistitor->Visit(this);
    }
};
