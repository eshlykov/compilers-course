#pragma once

#include "../visitor.hpp"
#include "statement.hpp"

class Expression;

class LoopStatement : public Statement {
public:
    LoopStatement(Expression* condition, Statement* statement) :
        condition_(condition), statement_(statement) {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Expression* condition_ = {};
    Statement* statement_ = {};
};