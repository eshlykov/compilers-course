#include "scope-statement.hpp"

ScopeStatement::ScopeStatement(Location location,
    std::vector<std::unique_ptr<Statement>>& statements) :
        statements_{std::move(statements)} {
    SetLocation(location);
    assert(statements_ != nullptr);
}

void ScopeStatement::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
