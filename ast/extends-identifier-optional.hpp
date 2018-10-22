#pragma once

#include <memory>
#include <optional>

class Idenitifier;

class ExtendsIdentifierOptional {
public:
    ExtendsIdentifierOptional(std::shared_ptr<Identifier> className) :
        className_{className} {
    }

public:
    std::optional<std::shared_ptr<Identifier>> className_ = {};
};
