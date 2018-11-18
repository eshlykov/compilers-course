#pragma once

#include "statement.hpp"
#include <memory>

class Expression;

class LoopStatement : public Statement {
public:
    LoopStatement(Location location,
        std::unique_ptr<Expression> condition,
        std::unique_ptr<Statement> statement) :
            condition_(std::move(condition)),
            statement_(std::move(statement)) {
        location_ = location;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::unique_ptr<Expression> condition_;
    std::unique_ptr<Statement> statement_;
};
