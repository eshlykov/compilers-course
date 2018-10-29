#pragma once

#include "../visitor.hpp"
#include "node.hpp"
#include <optional>

class Idenitifier;

class ExtendsIdentifierOptional : public Node {
public:
    ExtendsIdentifierOptional() = default;

    ExtendsIdentifierOptional(Identifier* className) :
        className_{className} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::optional<Identifier*> className_ = {};
};
