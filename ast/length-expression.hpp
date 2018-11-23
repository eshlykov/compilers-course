#pragma once

#include "expression.hpp"
#include <memory>

class LengthExpression : public Expression {
public:
    explicit LengthExpression(Location location,
        std::unique_ptr<Expression> expression);

    virtual void Accept(Visitor* visitor);

public:
    std::unique_ptr<Expression> expression_;
};
