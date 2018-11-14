#pragma once

#include "../visitor.hpp"
#include "expression.hpp"

class NotExpression : public Expression {
public:
    explicit NotExpression(Expression* expression) :
        expression_{expression} {
    }

    ~NotExpression() {
        delete expression_;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Expression* expression_;
};
