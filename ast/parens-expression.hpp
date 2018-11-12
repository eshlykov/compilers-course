#pragma once

#include "../visitor.hpp"
#include "expression.hpp"

class ParensExpression : public Expression {
public:
    explicit ParensExpression(Expression* expression) :
        expression_{expression} {
    }

    ~ParensExpression() {
        delete expression_;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Expression* expression_ = {};
};
