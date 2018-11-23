#include "scope-statement.hpp"

ScopeStatement::ScopeStatement(Location location,
    std::vector<std::unique_ptr<Statement>>& statements) :
        statements_{std::move(statements)} {
    location_ = location;
}

void ScopeStatement::Accept(Visitor* visitor) {
    visitor->Visit(this);
}