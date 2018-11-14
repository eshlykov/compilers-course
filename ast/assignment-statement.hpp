#pragma once

#include "../visitor.hpp"
#include "statement.hpp"
#include <memory>
#include <string>

class Expression;

class AssignmentStatement : public Statement {
public:
    AssignmentStatement(const std::string& variable,
        std::unique_ptr<Expression> expression) :
            variable_{variable},
            expression_{std::move(expression)} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    const std::string variable_;
    std::unique_ptr<Expression> expression_;
};
