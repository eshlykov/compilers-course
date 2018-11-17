#pragma once

#include "../visitor.hpp"
#include "expression.hpp"
#include <memory>

class LengthExpression : public Expression {
public:
    explicit LengthExpression(std::unique_ptr<Expression> expression) :
        expression_{std::move(expression)} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::unique_ptr<Expression> expression_;
};
