#pragma once

#include "statement.hpp"
#include "expression.hpp"
#include <memory>

class ConditionStatement : public Statement {
public:
    ConditionStatement(Location location,
        std::unique_ptr<Expression> condition,
        std::unique_ptr<Statement> ifStatement,
        std::unique_ptr<Statement> elseStatement);

    virtual void Accept(Visitor* visitor) override final;

public:
    const std::unique_ptr<Expression> condition_;
    const std::unique_ptr<Statement> ifStatement_;
    const std::unique_ptr<Statement> elseStatement_;
};
