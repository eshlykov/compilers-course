#pragma once

#include "ir-statement.hpp"
#include <memory>

class IrExpression;

class IrMove : public IrStatement {
public:
    IrMove(std::shared_ptr<IrExpression> destination, std::shared_ptr<IrExpression> source);

    virtual void Accept(IrVisitor* visitor) override final;

public:
    const std::shared_ptr<IrExpression> destination_;
    const std::shared_ptr<IrExpression> source_;
};
