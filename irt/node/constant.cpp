#include "constant.hpp"

namespace Irt {

    Constant::Constant(int value) :
        value_{value} {
    }

    void Constant::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
