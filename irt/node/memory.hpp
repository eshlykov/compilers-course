#pragma once

#include "expression.hpp"
#include <memory>

class Memory: public Expression {
public:
    explicit Memory(std::shared_ptr<Expression> expression);

    virtual void Accept(Visitor* visitor) override final;

public:
    const std::shared_ptr<Expression> expression_;
};
