#include "memory.hpp"

namespace Ct {

    Memory::Memory(std::shared_ptr<Expression> expression) :
        expression_{expression} {
        assert(expression_ != nullptr);
    }

    void Memory::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
