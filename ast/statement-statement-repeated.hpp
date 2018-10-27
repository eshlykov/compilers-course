#pragma once

#include "statement.hpp"

class StatementRepeated;

class StatementStatementRepeated : public Statement {
public:
    StatementStatementRepeated(StatementRepeated* statementRepeated) :
        statementRepeated_(statementRepeated) {
    };

public:
    StatementRepeated* statementRepeated_ = {};
};
