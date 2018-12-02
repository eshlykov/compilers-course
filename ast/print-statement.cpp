#include "print-statement.hpp"

PrintStatement::PrintStatement(Location location,
    std::unique_ptr<Expression> expression) :
        expression_{std::move(expression)} {
    SetLocation(location);
    assert(expression_ != nullptr);
}

void PrintStatement::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
