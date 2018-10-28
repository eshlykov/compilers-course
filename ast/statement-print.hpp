#pragma once

#include "../visitor.hpp"
#include "statement.hpp"

class Expression;

class StatementPrint : public Statement {
public:
    StatementPrint(Expression* expression) :
        expression_(expression) {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Expression* expression_ = {};
};
