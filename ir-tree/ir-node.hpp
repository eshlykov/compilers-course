#pragma once

#include "../utils/visitor.hpp"
#include <cassert>

class IrNode {
public:
    IrNode() = default;

    virtual ~IrNode() = default;

    virtual void Accept(Visitor*) = 0;
};
