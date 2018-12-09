#pragma once

#include "expression.hpp"

class NumberExpression : public Expression {
public:
    explicit NumberExpression(Location location,
        int value);

    virtual void Accept(Visitor* visitor) override final;

public:
    const int value_;
};
