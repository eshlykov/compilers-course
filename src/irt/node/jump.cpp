#include "jump.hpp"
#include "name.hpp"

namespace Irt {

    Jump::Jump(const Address& address) :
            expression_{std::make_shared<Name>(address)},
            addresses_{address} {
        assert(expression_ != nullptr);
    }

    void Jump::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
