#pragma once

#include "../visitor.hpp"
#include "expression.hpp"
#include <memory>

class IntArrayConstructorExpression : public Expression {
public:
    explicit IntArrayConstructorExpression(std::unique_ptr<Expression> expression) :
        expression_{std::move(expression)} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::unique_ptr<Expression> expression_;
};
