#pragma once

#include "statement.hpp"

class Expression;

class StatementWhile : public Statement {
public:
    StatementWhile(Expression* condition, Statement* trueStatement) :
        condition_(condition),
        trueStatement_(trueStatement) {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    Expression* condition_ = {};
    Statement* trueStatement_ = {};
};
