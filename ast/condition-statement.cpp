#include "condition-statement.hpp"

ConditionStatement::ConditionStatement(Location location,
    std::unique_ptr<Expression> condition,
    std::unique_ptr<Statement> ifStatement,
    std::unique_ptr<Statement> elseStatement) :
        condition_{std::move(condition)},
        ifStatement_{std::move(ifStatement)},
        elseStatement_{std::move(elseStatement)} {
    SetLocation(location);
}

void ConditionStatement::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
