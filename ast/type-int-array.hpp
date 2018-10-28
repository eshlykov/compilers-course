#pragma once

#include "type.hpp"

class TypeIntArray : public Type {
public:
    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};
