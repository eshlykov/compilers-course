#pragma once

#include "ir-expression.hpp"
#include <memory>

class IrLabel;

class IrName : public IrExpression {
public:
    explicit IrName(std::shared_ptr<IrLabel> label);

    virtual void Accept(IrVisitor* visitor) override final;

public:
    const std::shared_ptr<IrLabel> label_;
};
