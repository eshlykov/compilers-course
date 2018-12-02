#pragma once

#include "expression.hpp"

class ThisExpression : public Expression {
public:
    explicit ThisExpression(Location location);

    virtual void Accept(Visitor* visitor) override final;
};
