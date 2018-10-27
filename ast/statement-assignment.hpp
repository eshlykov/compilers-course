#pragma once

#include "statement.hpp"
#include <memory>

class Expression;
class Identifier;

class StatementAssignment : public Statement {
public:
    StatementAssignment(std::shared_ptr<Identifier> identifier,
        std::shared_ptr<Expression> expression) :
            identifier_(identifier),
            expression_(expression) {
    }

public:
    std::shared_ptr<Identifier> identifier_ = {};
    std::shared_ptr<Expression> expression_ = {};
};
