#include "name.hpp"

namespace Irt {

    Name::Name(const Address& address) :
        address_{address} {
    }

    void Name::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
