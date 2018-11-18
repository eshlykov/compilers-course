#pragma once

#include "../visitor.hpp"
#include "statement.hpp"
#include <memory>
#include <string>

class Expression;

class AssignmentStatement : public Statement {
public:
    AssignmentStatement(Location location,
        const std::string& variable,
        std::unique_ptr<Expression> expression);

    virtual void Accept(Visitor* visitor) override final;

public:
    const std::string variable_;
    std::unique_ptr<Expression> expression_;
};
