#pragma once

#include "../visitor.hpp"
#include "statement.hpp"
#include <string>

class Expression;

class AssignmentStatement : public Statement {
public:
    AssignmentStatement(const std::string& variable, Expression* expression) :
        variable_{variable}, expression_(expression) {
    }

    ~AssignmentStatement() {
        delete expression_;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::string variable_ = {};
    Expression* expression_ = {};
};
