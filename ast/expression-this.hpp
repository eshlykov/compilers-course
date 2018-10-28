#pragma once

#include "expression.hpp"

class ExpressionThis : public Expression {
public:
    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};
