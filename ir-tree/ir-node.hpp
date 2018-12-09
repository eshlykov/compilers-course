#pragma once

#include "../utils/ir-visitor.hpp"
#include <cassert>

class IrNode {
public:
    IrNode() = default;

    virtual ~IrNode() = default;

    virtual void Accept(IrVisitor*) = 0;
};
