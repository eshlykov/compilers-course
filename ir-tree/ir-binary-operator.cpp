#include "ir-binary-operator.hpp"

IrBinaryOperator::IrBinaryOperator(IrArithmeticOperator arithmeticOperator,
    std::shared_ptr<IrExpression> left,
    std::shared_ptr<IrExpression> right) :
        arithmeticOperator_{arithmeticOperator},
        right_{right},
        left_{left} {
}

void IrBinaryOperator::Accept(IrVisitor* visitor) {
    visitor->Visit(this);
}
