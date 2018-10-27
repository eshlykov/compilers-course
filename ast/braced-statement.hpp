#pragma once

#include "statement.hpp"

class StatementRepeated;

class BracedStatement : public Statement {
public:
    BracedStatement(StatementRepeated* statementRepeated) :
        statementRepeated_(statementRepeated) {
    };

public:
    StatementRepeated* statementRepeated_ = {};
};
