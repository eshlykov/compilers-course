#include "jump.hpp"

namespace Irt {

    Jump::Jump(std::shared_ptr<Expression> expression,
        const std::vector<std::shared_ptr<Label>>& labels) :
            expression_{expression},
            labels_{labels} {
        assert(expression_ != nullptr);
    }

    void Jump::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
