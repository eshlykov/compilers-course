#pragma once

#include "statement.hpp"
#include <memory>
#include <vector>

class ScopeStatement : public Statement {
public:
    explicit ScopeStatement(Location location,
        std::vector<std::unique_ptr<Statement>>& statements);


    virtual void Accept(Visitor* visitor) override final;

public:
    std::vector<std::unique_ptr<Statement>> statements_;
};
