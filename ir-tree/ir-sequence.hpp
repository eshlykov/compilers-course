#pragma once

#include "ir-statement.hpp"
#include <memory>

class IrSequence : public IrStatement {
public:
    IrSequence(std::shared_ptr<IrStatement> leftStatement,
        std::shared_ptr<IrStatement> rightStatement);

    virtual void Accept(IrVisitor* visitor) override final;

public:
    const std::shared_ptr<IrStatement> leftStatement_;
    const std::shared_ptr<IrStatement> rightStatement_;
};
