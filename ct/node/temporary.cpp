#include "temporary.hpp"

namespace Ct {

    Temporary::Temporary(Storage storage) :
        storage_(storage) {
    }

    void Temporary::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
