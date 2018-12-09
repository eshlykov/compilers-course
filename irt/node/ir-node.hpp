#pragma once

#include "../visitor/ir-visitor.hpp"
#include <cassert>

class IrNode {
public:
    IrNode() = default;

    virtual ~IrNode() = default;

    virtual void Accept(IrVisitor*) = 0;
};
