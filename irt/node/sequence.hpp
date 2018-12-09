#pragma once

#include "statement.hpp"
#include <memory>

class Sequence : public Statement {
public:
    Sequence(std::shared_ptr<Statement> leftStatement,
        std::shared_ptr<Statement> rightStatement);

    virtual void Accept(Visitor* visitor) override final;

public:
    const std::shared_ptr<Statement> leftStatement_;
    const std::shared_ptr<Statement> rightStatement_;
};
