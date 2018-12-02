#pragma once

#include "expression.hpp"
#include <memory>

class IntArrayConstructorExpression : public Expression {
public:
    explicit IntArrayConstructorExpression(Location location,
        std::unique_ptr<Expression> expression);

    virtual void Accept(Visitor* visitor) override final;

public:
    const std::unique_ptr<Expression> expression_;
};
