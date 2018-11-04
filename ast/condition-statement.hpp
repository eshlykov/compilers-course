#pragma once

#include "../visitor.hpp"
#include "statement.hpp"

class Expression;

class ConditionStatement : public Statement {
public:
    ConditionStatement(Expression* condition, Statement* ifStatement, Statement* elseStatement) :
        condition_{condition}, ifStatement_{ifStatement}, elseStatement_{elseStatement} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Expression* condition_ = {};
    Statement* ifStatement_ = {};
    Statement* elseStatement_ = {};
};
