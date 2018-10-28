#pragma once

#include "../visitor.hpp"
#include "type.hpp"

class Identifier;

class TypeIdentifier : public Type {
public:
    TypeIdentifier(Identifier* className) :
        className_(className) {
    };

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    Identifier* className_ = {};
};
