#pragme once

#include "statement.hpp"
#include <memory>

class Expression;

class StatementWhile : public Statement {
public:
    StatementWhile(std::shared_ptr<Expression> condition,
        std::shared_ptr<Statement> trueStatement) :
            condition_(condition),
            trueStatement_(trueStatement) {

    }

public:
    std::shared_ptr<Expression> condition_ = {};
    std::shared_ptr<Statement> trueStatement_ = {};
};
