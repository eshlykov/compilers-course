#include "class-body.hpp"

namespace Ast {

    ClassBody::ClassBody(Location location,
        std::vector<std::unique_ptr<VarDeclaration>>& variables,
        std::vector<std::unique_ptr<MethodDeclaration>>& methods) :
            variables_{std::move(variables)},
            methods_{std::move(methods)} {
        SetLocation(location);
    }

    void ClassBody::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
