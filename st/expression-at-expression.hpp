#pragma once

#include "../visitor.hpp"
#include "expression.hpp"

class ExpressionAtExpression : public Expression {
public:
    ExpressionAtExpression(Expression* lhs, Expression* rhs) :
        lhs_{lhs},
        rhs_{rhs} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Expression* lhs_ = {};
    Expression* rhs_ = {};
};
