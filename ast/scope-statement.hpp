#pragma once

#include "../visitor.hpp"
#include "statement.hpp"
#include <memory>
#include <vector>

class ScopeStatement : public Statement {
public:
    explicit ScopeStatement(std::vector<std::unique_ptr<Statement>>& statements) :
        statements_{std::move(statements)} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::vector<std::unique_ptr<Statement>> statements_;
};
