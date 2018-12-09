#include "this-expression.hpp"

class Type;

namespace Ast {

    ThisExpression::ThisExpression(Location location) {
        SetLocation(location);
    }

    void ThisExpression::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
