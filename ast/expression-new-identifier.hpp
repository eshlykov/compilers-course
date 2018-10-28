#pragma once

#include "expression.hpp"

class Identifier;

class ExpressionNewIdentifier : public Expression {
public:
    ExpressionNewIdentifier(Identifier* identifier) : identifier_{identifier} {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    Identifier* identifier_ = {};
};
