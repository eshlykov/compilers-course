#include "call.hpp"

namespace Ct {

    Call::Call(std::shared_ptr<Expression> expression,
        const std::vector<std::shared_ptr<Expression>>& expressionList) :
            expression_(expression),
            expressionList_(expressionList) {
        assert(expression_ != nullptr);
    }

    void Call::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
