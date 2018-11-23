#include "print-statement.hpp"

PrintStatement::PrintStatement(Location location,
    std::unique_ptr<Expression> expression) :
        expression_{std::move(expression)} {
    location_ = location;
}

void PrintStatement::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
