#include "ir-conditional-jump.hpp"

IrConditionalJump::IrConditionalJump(IrLogicalOperator logicalOperator,
    std::shared_ptr<IrExpression> expressionLeft,
    std::shared_ptr<IrExpression> expressionRight,
    std::shared_ptr<IrLabel> labelIf,
    std::shared_ptr<IrLabel> labelElse) :
        logicalOperator_{logicalOperator},
        expressionLeft_{expressionLeft},
        expressionRight_{expressionRight},
        labelIf_{labelIf},
        labelElse_{labelElse} {
    assert(expressionLeft_ != nullptr);
    assert(expressionRight_ != nullptr);
    assert(labelIf_ != nullptr);
    assert(labelElse_ != nullptr);
}

void IrConditionalJump::Accept(IrVisitor* visitor) {
    visitor->Visit(this);
}
