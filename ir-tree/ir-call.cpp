#include "ir-call.hpp"

IrCall::IrCall(std::shared_ptr<IrExpression> expression,
    const std::vector<std::shared_ptr<IrExpression>>& expressionList) :
        expression_(expression),
        expressionList_(expressionList) {
}

void IrCall::Accept(IrVisitor* visitor) {
    visitor->Visit(this);
}
