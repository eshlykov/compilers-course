#pragma once

#include "../visitor.hpp"
#include "expression.hpp"

class ExpressionFalse : public Expression {
public:
    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};
