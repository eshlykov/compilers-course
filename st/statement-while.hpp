#pragma once

#include "../visitor.hpp"
#include "statement.hpp"

class Expression;

class StatementWhile : public Statement {
public:
    StatementWhile(Expression* condition, Statement* trueStatement) :
        condition_(condition),
        trueStatement_(trueStatement) {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Expression* condition_ = {};
    Statement* trueStatement_ = {};
};
