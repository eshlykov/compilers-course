#pragma once

#include "../visitor.hpp"
#include "expression.hpp"

class ExpressionThis : public Expression {
public:
    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};
