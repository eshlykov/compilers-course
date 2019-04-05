#include "type.hpp"

namespace Ast {

    Type::Type(Location location, const std::string& className) :
        type_{className} {
        SetLocation(location);
    }

    Type::Type(Location location, TypeKind typeKind) :
        type_{typeKind} {
        SetLocation(location);
    }

    void Type::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
