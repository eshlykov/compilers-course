#pragma once

#include "statement.hpp"
#include <memory>

class Expression;
class Identifier;

class StatementAssignment : public Statement {
public:
    StatementAssignment(Identifier* identifier, Expression* expression) :
        identifier_(identifier), expression_(expression) {
    }

public:
    Identifier* identifier_ = {};
    Expression* expression_ = {};
};
