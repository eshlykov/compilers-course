#pragma once

#include "statement.hpp"
#include <memory>

class StatementRepeated;

class StatementStatementRepeated : public Statement {
public:
    StatementStatementRepeated(std::shared_ptr<StatementRepeated> statementRepeated) :
        statementRepeated_(statementRepeated) {
    };

public:
    std::shared_ptr<StatementRepeated> statementRepeated_ = {};
};
