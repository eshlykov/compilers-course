#pragma once

#include "../visitor.hpp"
#include "statement.hpp"
#include <vector>

class ScopeStatement : public Statement {
public:
    ScopeStatement(const std::vector<Statement*>& statements) :
        statements_{statements} {
    }

    ~ScopeStatement() {
        FreeVector(statements_);
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::vector<Statement*> statements_ = {};
};
