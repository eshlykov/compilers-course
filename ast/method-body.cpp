#include "method-body.hpp"

MethodBody::MethodBody(Location location,
    std::vector<std::unique_ptr<VarDeclaration>>& variables,
    std::vector<std::unique_ptr<Statement>>& statements,
    std::unique_ptr<Expression> returnExpression) :
        variables_{std::move(variables)},
        statements_{std::move(statements)},
        returnExpression_{std::move(returnExpression)} {
    SetLocation(location);
    assert(expresson_ != nullptr);
}

void MethodBody::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
