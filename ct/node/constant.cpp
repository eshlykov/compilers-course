#include "constant.hpp"

namespace Ct {

    Constant::Constant(int value) :
        value_{value} {
    }

    void Constant::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
