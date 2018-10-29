#pragma once

#include "../visitor.hpp"
#include "expression.hpp"

class ExpressionTrue : public Expression {
public:
    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }
};
