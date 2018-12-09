#pragma once

#include "ir-expression.hpp"
#include <memory>
#include <vector>

class IrCall : public IrExpression {
public:
    IrCall(std::shared_ptr<IrExpression> expression,
        const std::vector<std::shared_ptr<IrExpression>>& expressionList);

    virtual void Accept(IrVisitor* visitor) override final;

public:
    const std::shared_ptr<IrExpression> expression_;
    const std::vector<std::shared_ptr<IrExpression>> expressionList_;
};
