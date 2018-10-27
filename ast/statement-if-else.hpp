#pragma once

#include "statement.hpp"

class Expression;

class StatementIfElse : public Statement {
public:
    StatementIfElse(Expression* condition, Statement* trueStatement, Statement* falseStatement) :
        condition_(condition), trueStatement_(trueStatement), falseStatement_(falseStatement) {
    }

public:
    Expression* condition_ = {};
    Statement* trueStatement_ = {};
    Statement* falseStatement_ = {};
};
