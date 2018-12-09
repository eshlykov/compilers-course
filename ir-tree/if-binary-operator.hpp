#pragma once

#include "ir-expression.hpp"
#include <memory>

enum class IrArithmeticOperator {
    Plus, Minus, Multiplication
};


class IrBinaryOperator : public IrExpression {
public:
    IrBinaryOperator(IrArithmeticOperator binaryOperator,
        std::shared_ptr<IrExpression> left,
        std::shared_ptr<IrExpression> right);

    virtual void Accept(IrVisitor* visitor) override final;

public:
    const IrArithmeticOperator arithmeticOperator_;
    std::shared_ptr<IrExpression> left_;
    std::shared_ptr<IrExpression> right_;
};
