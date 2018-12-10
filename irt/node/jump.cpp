#include "jump.hpp"
#include "name.hpp"

namespace Irt {

    Jump::Jump(std::shared_ptr<Expression> expression,
        const std::vector<Address>& addresses) :
            expression_{expression},
            addresses_{addresses} {
        assert(expression_ != nullptr);
    }

    Jump::Jump(const Address& address) :
            expression_{std::make_shared<Name>(address)},
            addresses_{address} {
        assert(expression_ != nullptr);
    }

    void Jump::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
