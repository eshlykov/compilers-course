#pragma once

#include "../visitor.hpp"
#include <optional>

class Idenitifier;

class ExtendsIdentifierOptional {
public:
    ExtendsIdentifierOptional() = default;

    ExtendsIdentifierOptional(Identifier* className) :
        className_{className} {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    std::optional<Identifier*> className_ = {};
};
