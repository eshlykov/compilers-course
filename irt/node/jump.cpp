#include "jump.hpp"
#include "name.hpp"

namespace Irt {

    Jump::Jump(std::shared_ptr<Expression> expression,
        const std::vector<Address>& labels) :
            expression_{expression},
            labels_{labels} {
        assert(expression_ != nullptr);
    }

    Jump::Jump(const Address& label) :
            expression_{std::make_shared<Name>(label)},
            labels_{label} {
        assert(expression_ != nullptr);
    }

    void Jump::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
