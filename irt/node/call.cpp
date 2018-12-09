#include "call.hpp"

Call::Call(std::shared_ptr<Expression> expression,
    const std::vector<std::shared_ptr<Expression>>& expressionList) :
        expression_(expression),
        expressionList_(expressionList) {
}

void Call::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
