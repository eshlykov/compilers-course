#pragma once

#include "ir-expression.hpp"
#include <memory>
#include <string>

class IrTemporary : public IrExpression {
public:
    explicit IrTemporary(const std::string& temporary);

    virtual void Accept(IrVisitor* visitor) override final;

public:
    const std::string temporary_;
};
