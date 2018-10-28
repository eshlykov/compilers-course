#pragma once

#include "../visitor.hpp"
#include "statement.hpp"

class StatementRepeated;

class BracedStatement : public Statement {
public:
    BracedStatement(StatementRepeated* statementRepeated) :
        statementRepeated_(statementRepeated) {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    StatementRepeated* statementRepeated_ = {};
};
