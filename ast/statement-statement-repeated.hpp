#pragma once

#include "statement.hpp"

class StatementRepeated;

class BracedStatementRepeated : public Statement {
public:
    BracedStatementRepeated(StatementRepeated* statementRepeated) :
        statementRepeated_(statementRepeated) {
    };

public:
    StatementRepeated* statementRepeated_ = {};
};
