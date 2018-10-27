#pragma once

#include "statement.hpp"
#include <memory>

class Expression;
class Identifier;

class StatementAssignmentArray : public Statement {
public:
    StatementAssignmentArray(std::shared_ptr<Identifier> identifier,
        std::shared_ptr<Expression> expressionFirst,
        std::shared_ptr<Expression> expressionSecond) :
            identifier_(identifier),
            expressionFirst_(expressionFirst),
            expressionSecond_(expressionSecond) {
    }

public:
    std::shared_ptr<Identifier> identifier_ = {};
    std::shared_ptr<Expression> expressionFirst_ = {};
    std::shared_ptr<Expression> expressionSecond_ = {};
};
