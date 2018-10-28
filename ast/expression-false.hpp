#pragma once

#include "../visitor.hpp"
#include "expression.hpp"

class ExpressionFalse : public Expression {
public:
    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }
};
