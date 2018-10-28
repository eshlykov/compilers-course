#pragma once

#include "../visitor.hpp"
#include "statement.hpp"
#include <memory>

class Expression;
class Identifier;

class StatementAssignment : public Statement {
public:
    StatementAssignment(Identifier* identifier, Expression* expression) :
        identifier_(identifier), expression_(expression) {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    Identifier* identifier_ = {};
    Expression* expression_ = {};
};
