#include "loop-statement.hpp"

LoopStatement::LoopStatement(Location location,
    std::unique_ptr<Expression> condition,
    std::unique_ptr<Statement> statement) :
        condition_(std::move(condition)),
        statement_(std::move(statement)) {
    location_ = location;
}

void LoopStatement::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
