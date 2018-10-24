#pragma once

#include <vector>
#include <memory>

class Statement;

class StatementRepeated {
public:
    StatementRepeated(const std::vector<std::shared_ptr<Statement>>& statementRepeated) :
        statementRepeated_{statementRepeated} {

    }
public:
    std::vector<std::shared_ptr<Statement>> statementRepeated_ = {};
};
