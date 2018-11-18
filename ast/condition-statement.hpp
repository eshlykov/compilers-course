#pragma once

#include "statement.hpp"
#include <memory>

class Expression;

class ConditionStatement : public Statement {
public:
    ConditionStatement(Location location,
        std::unique_ptr<Expression> condition,
        std::unique_ptr<Statement> ifStatement,
        std::unique_ptr<Statement> elseStatement) :
            condition_{std::move(condition)},
            ifStatement_{std::move(ifStatement)},
            elseStatement_{std::move(elseStatement)} {
        location_ = location;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::unique_ptr<Expression> condition_;
    std::unique_ptr<Statement> ifStatement_;
    std::unique_ptr<Statement> elseStatement_;
};
