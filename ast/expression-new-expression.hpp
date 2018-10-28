#pragma once

#include "../visitor.hpp"
#include "expression.hpp"

class ExpressionNewExpression : public Expression {
public:
    ExpressionNewExpression(Expression* expression) : expression_{expression} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Expression* expression_ = {};
};
