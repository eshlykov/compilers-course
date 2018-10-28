#pragma once

#include "../visitor.hpp"
#include "type.hpp"

class Identifier;

class TypeIdentifier : public Type {
public:
    TypeIdentifier(Identifier* className) :
        className_(className) {
    };

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Identifier* className_ = {};
};
