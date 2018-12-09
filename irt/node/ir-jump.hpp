#pragma once

#include "ir-statement.hpp"
#include <memory>
#include <vector>

class IrExpression;
class IrLabel;

class IrJump : public IrStatement {
public:
    IrJump(std::shared_ptr<IrExpression> expression,
        const std::vector<std::shared_ptr<IrLabel>>& labels);

    virtual void Accept(IrVisitor* visitor) override final;

public:
    const std::shared_ptr<IrExpression> expression_;
    const std::vector<std::shared_ptr<IrLabel>> labels_;
};
