#pragma once

#include "type.hpp"

class Identifier;

class TypeIdentifier : public Type {
public:
    TypeIdentifier(std::shared_ptr<Identifier> className) :
        Type(className) {
    };
};
