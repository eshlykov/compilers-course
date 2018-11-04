#pragma once

#include "../visitor.hpp"
#include "statement.hpp"

class Expression;

class AssignmentByIndexStatement : public Statement {
public:
    AssignmentByIndexStatement(const std::string& array, Expression* index, Expression* expression) :
        array_{array}, index_{index}, expression_{expression} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::string array_ = {};
    Expression* index_ = {};
    Expression* expression_ = {};
};
