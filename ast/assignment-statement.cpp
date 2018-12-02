#include "assignment-statement.hpp"

AssignmentStatement::AssignmentStatement(Location location,
    const std::string& variable,
    std::unique_ptr<Expression> expression) :
        variable_{variable},
        expression_{std::move(expression)} {
    SetLocation(location);
}

void AssignmentStatement::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
