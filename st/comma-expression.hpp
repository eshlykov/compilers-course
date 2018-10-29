#pragma once

#include "../visitor.hpp"
#include "node.hpp"

class Expression;

class CommaExpression : public Node {
public:
    CommaExpression(Expression* expression) :
        expression_{expression} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Expression* expression_ = {};
};
