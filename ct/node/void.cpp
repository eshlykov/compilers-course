#include "void.hpp"

namespace Ct {

    Void::Void(std::shared_ptr<Expression> expression) :
        expression_{expression} {
        assert(expression_ != nullptr);
    }

    void Void::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
