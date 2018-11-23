#include "var-declaration.hpp"

VarDeclaration::VarDeclaration(Location location,
    std::unique_ptr <Type> type,
    const std::string &name) :
        type_{std::move(type)},
        name_{name} {
    location_ = location;
}
void VarDeclaration::Accept(Visitor* visitor) {
    visitor->Visit(this);
}