#pragma once

#include "ir-expression.hpp"

class IrConstant : public IrExpression {
public:
    explicit IrConstant(int value);

    virtual void Accept(IrVisitor* visitor) override final;

private:
    const int value_;
};
