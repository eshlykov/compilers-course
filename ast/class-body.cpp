#include "class-body.hpp"

ClassBody::ClassBody(Location location,
    std::vector<std::unique_ptr<VarDeclaration>>& variables,
    std::vector<std::unique_ptr<MethodDeclaration>>& methods) :
        variables_{std::move(variables)},
        methods_{std::move(methods)} {
    location_ = location;
}

void ClassBody::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
