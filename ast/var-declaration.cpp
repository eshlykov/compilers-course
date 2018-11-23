#include "var-declaration.hpp"

VarDeclaration::VarDeclaration(Location location,
    std::unique_ptr <Type> type,
    const std::string &name) :
        type_{std::move(type)},
        name_{name} {
    location_ = location;
}
virtual void VarDeclaration::Accept(Visitor* visitor) override final {
    visitor->Visit(this);
}