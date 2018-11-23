#include "type.hpp"

Type::Type(Location location, const std::string& className) :
    type_{className} {
    location_ = location;
}

Type::Type(Location location, TypeKind typeKind) :
    type_{typeKind} {
    location_ = location;
}

void Type::Accept(Visitor* visitor) {
    visitor->Visit(this);
}