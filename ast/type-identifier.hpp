#pragma once

#include "type.hpp"

class Identifier;

class TypeIdentifier : public Type {
public:
    TypeIdentifier(Identifier* className) :
        Type(className) {
    };
};
