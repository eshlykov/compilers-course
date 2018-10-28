#pragma once

#include "../visitor.hpp"
#include "statement.hpp"

class StatementRepeated;

class BracedStatement : public Statement {
public:
    BracedStatement(StatementRepeated* statementRepeated) :
        statementRepeated_(statementRepeated) {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    StatementRepeated* statementRepeated_ = {};
};
