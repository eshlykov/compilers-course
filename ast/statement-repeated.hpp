#pragma once

#include <vector>

class Statement;

class StatementRepeated {
public:
    StatementRepeated(const std::vector<Statement*>& statementRepeated) :
        statementRepeated_{statementRepeated} {
    }

public:
    std::vector<Statement*> statementRepeated_ = {};
};
