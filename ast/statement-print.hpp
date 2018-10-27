#pragma once

#include "statement.hpp"
#include <memory>

class Expression;

class StatementPrint : public Statement {
public:
    StatementPrint(std::shared_ptr<Expression> expression) :
        expression_(expression) {

    }

public:
    std::shared_ptr<Expression> expression_ = {};
};
