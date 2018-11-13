#pragma once

#include "../visitor.hpp"
#include "statement.hpp"

class Expression;

class PrintStatement : public Statement {
public:
    explicit PrintStatement(Expression* expression) :
        expression_(expression) {
    }

    ~PrintStatement() {
        delete expression_;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Expression* expression_ = {};
};
