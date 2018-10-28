#pragma once

#include "../visitor.hpp"
#include <vector>

class Statement;

class StatementRepeated {
public:
    StatementRepeated() = default;

    StatementRepeated(const std::vector<Statement*>& statementRepeated) :
        statementRepeated_{statementRepeated} {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    std::vector<Statement*> statementRepeated_ = {};
};
