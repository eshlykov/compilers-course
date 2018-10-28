#pragma once

#include "statement.hpp"

class Expression;
class Identifier;

class StatementAssignmentArray : public Statement {
public:
    StatementAssignmentArray(Identifier* identifier, Expression* expressionFirst, Expression* expressionSecond) :
        identifier_(identifier), expressionFirst_(expressionFirst), expressionSecond_(expressionSecond) {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    Identifier* identifier_ = {};
    Expression* expressionFirst_ = {};
    Expression* expressionSecond_ = {};
};
