#pragme once

#include "statement.hpp"

class Expression;

class StatementWhile : public Statement {
public:
    StatementWhile(Expression* condition, Statement* trueStatement) :
        condition_(condition),
        trueStatement_(trueStatement) {

    }

public:
    Expression* condition_ = {};
    Statement* trueStatement_ = {};
};
