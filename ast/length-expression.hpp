#pragma once

#include "../visitor.hpp"
#include "expression.hpp"

class LengthExpression : public Expression {
public:
    explicit LengthExpression(Expression* expression) :
        expression_{expression} {
    }

    ~LengthExpression() {
        delete expression_;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Expression* expression_ = {};
};
