#include "assignment-by-index-statement.hpp"

AssignmentByIndexStatement::AssignmentByIndexStatement(Location location,
    const std::string& array,
    std::unique_ptr<Expression> index,
    std::unique_ptr<Expression> expression) :
        array_{array},
        index_{std::move(index)},
        expression_{std::move(expression)} {
    location_ = location;
}

void AssignmentByIndexStatement::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
