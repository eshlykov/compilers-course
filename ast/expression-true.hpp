#pragma once

#include "expression.hpp"

class ExpressionTrue : public Expression {
public:
    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};
