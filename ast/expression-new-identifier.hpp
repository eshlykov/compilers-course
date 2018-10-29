#pragma once

#include "../visitor.hpp"
#include "expression.hpp"

class Identifier;

class ExpressionNewIdentifier : public Expression {
public:
    ExpressionNewIdentifier(Identifier* identifier) :
        identifier_{identifier} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Identifier* identifier_ = {};
};
