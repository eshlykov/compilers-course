#pragma once

#include "ir-expression.hpp"
#include <memory>

enum class IrArithmeticOperator {
    Plus,
    Minus,
    Multiplication
};

class IrBinaryOperator : public IrExpression {
public:
    IrBinaryOperator(IrArithmeticOperator arithmeticOperator,
        std::shared_ptr<IrExpression> left,
        std::shared_ptr<IrExpression> right);

    virtual void Accept(IrVisitor* visitor) override final;

public:
    const IrArithmeticOperator arithmeticOperator_;
    const std::shared_ptr<IrExpression> left_;
    const std::shared_ptr<IrExpression> right_;
};
