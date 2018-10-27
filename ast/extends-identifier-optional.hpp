#pragma once

#include <optional>

class Idenitifier;

class ExtendsIdentifierOptional {
public:
    ExtendsIdentifierOptional() = default;

    ExtendsIdentifierOptional(Identifier* className) :
        className_{className} {
    }

public:
    std::optional<Identifier*> className_ = {};
};
