#pragma once

#include "../visitor.hpp"
#include "node.hpp"
#include <vector>

class Statement;

class StatementRepeated : public Node {
public:
    StatementRepeated() = default;

    StatementRepeated(const std::vector<Statement*>& statementRepeated) :
        statementRepeated_{statementRepeated} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::vector<Statement*> statementRepeated_ = {};
};
