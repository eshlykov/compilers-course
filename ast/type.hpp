#pragma once

#include "../visitor.hpp"

class Identifier;

class Type {
public:
    Type() = default;

    Type(Identifier* className) :
        className_(className) {
    };

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    Identifier* className_ = {};
};
