#pragma once

#include "ir-statement.hpp"
#include <memory>
#include <string>

class IrLabel : public IrStatement {
public:
    explicit IrLabel(const std::string& label);

    virtual void Accept(IrVisitor* visitor) override final;

public:
    const std::string label_;
};
