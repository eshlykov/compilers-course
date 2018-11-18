#pragma once

#include "expression.hpp"
#include <memory>

class IntArrayConstructorExpression : public Expression {
public:
    explicit IntArrayConstructorExpression(Location location,
        std::unique_ptr<Expression> expression) :
            expression_{std::move(expression)} {
        location_ = location;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::unique_ptr<Expression> expression_;
};
