#pragma once

#include "type.hpp"

class TypeInt : public Type {
public:
    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};
