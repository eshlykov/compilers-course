#pragma once

#include "../visitor.hpp"
#include "type.hpp"

class TypeBoolean : public Type {
public:
    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }
};
