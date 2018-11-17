#pragma once

#include "../visitor.hpp"
#include "statement.hpp"
#include <memory>

class Expression;

class PrintStatement : public Statement {
public:
    explicit PrintStatement(std::unique_ptr<Expression> expression) :
        expression_{std::move(expression)} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::unique_ptr<Expression> expression_;
};
