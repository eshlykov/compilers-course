#pragma once

#include "type.hpp"

class TypeBoolean : public Type {
public:
    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};
