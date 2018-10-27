#pragma once

#include "statement.hpp"

class Expression;

class StatementPrint : public Statement {
public:
    StatementPrint(Expression* expression) :
        expression_(expression) {

    }

public:
    Expression* expression_ = {};
};
