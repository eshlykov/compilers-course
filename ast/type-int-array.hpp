#pragma once

#include "../visitor.hpp"
#include "type.hpp"

class TypeIntArray : public Type {
public:
    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};
