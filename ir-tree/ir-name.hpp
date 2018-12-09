#pragma once

#include "ir-expression.hpp"
#include <memory>

class IrLabel;

class IrName : public IrExpression {
public:
    IrName(std::shared_ptr<IrLabel> label);
    virtual void Accept(IrVisitor* visitor) override final;

public:
    std::shares_ptr<IrLabel> label_;
};
