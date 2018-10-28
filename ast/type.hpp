#pragma once

#include "../visitor.hpp"

class Identifier;

class Type {
public:
    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};
