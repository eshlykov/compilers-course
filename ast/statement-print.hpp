#pragma once

#include "statement.hpp"

class Expression;

class StatementPrint : public Statement {
public:
    StatementPrint(Expression* expression) :
        expression_(expression) {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    Expression* expression_ = {};
};
