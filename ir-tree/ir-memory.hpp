#pragma once

#include "ir-expression.hpp"
#include <memory>

class IrMemory: public IrExpression {
public:
    IrMemory(std::shared_ptr<IrExpression> expression);

    virtual void Accept(IrVisitor* visitor) override final;

public:
    const std::shared_ptr<IrExpression> expression_;
};
