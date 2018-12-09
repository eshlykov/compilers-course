#pragma once

#include "statement.hpp"
#include "expression.hpp"
#include <memory>

class PrintStatement : public Statement {
public:
    explicit PrintStatement(Location location,
        std::unique_ptr<Expression> expression);

    virtual void Accept(Visitor* visitor) override final;

public:
    const std::unique_ptr<Expression> expression_;
};
