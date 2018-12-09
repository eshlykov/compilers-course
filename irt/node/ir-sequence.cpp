#include "ir-sequence.hpp"

IrSequence::IrSequence(std::shared_ptr<IrStatement> leftStatement,
    std::shared_ptr<IrStatement> rightStatement) :
        leftStatement_{leftStatement},
        rightStatement_{rightStatement} {
}

void IrSequence::Accept(IrVisitor* visitor) {
    visitor->Visit(this);
}
