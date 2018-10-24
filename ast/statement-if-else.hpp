#pragma once

#include "statement.hpp"
#include <memory>

class Expression;

class StatementIfElse : public Statement {
public:
    StatementIfElse(std::shared_ptr<Expression> condition,
        std::shared_ptr<Statement> trueStatement,
        std::shared_ptr<Statement> falseStatement) :
            condition_(condition),
            trueStatement_(trueStatement),
            falseStatement_(falseStatement) {
    }

public:
    std::shared_ptr<Expression> condition_ = {};
    std::shared_ptr<Statement> trueStatement_ = {};
    std::shared_ptr<Statement> falseStatement_ = {};
};
