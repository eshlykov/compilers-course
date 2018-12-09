#include "name.hpp"

namespace Irt {

    Name::Name(Address label) :
        label_{label} {
    }

    void Name::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
