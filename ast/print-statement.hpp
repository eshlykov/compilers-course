#pragma once

#include "statement.hpp"
#include "expression.hpp"
#include <memory>

class PrintStatement : public Statement {
public:
    explicit PrintStatement(Location location,
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
