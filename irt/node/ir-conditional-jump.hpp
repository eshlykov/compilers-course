#pragma once

#include "ir-statement.hpp"
#include <memory>

class IrExpression;
class IrLabel;

enum class IrLogicalOperator {
    And,
    Less
};

class IrConditionalJump : public IrStatement {
public:
    IrConditionalJump(IrLogicalOperator logicalOperator,
        std::shared_ptr<IrExpression> expressionLeft,
        std::shared_ptr<IrExpression> expressionRight,
        std::shared_ptr<IrLabel> labelIf,
        std::shared_ptr<IrLabel> labelElse);

    virtual void Accept(IrVisitor* visitor) override final;

public:
    const IrLogicalOperator logicalOperator_;
    const std::shared_ptr<IrExpression> expressionLeft_;
    const std::shared_ptr<IrExpression> expressionRight_;
    const std::shared_ptr<IrLabel> labelIf_;
    const std::shared_ptr<IrLabel> labelElse_;
};
