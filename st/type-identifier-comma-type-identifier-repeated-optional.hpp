#pragma once

#include "../visitor.hpp"
#include "node.hpp"
#include <optional>

class TypeIdentifierCommaTypeIdentifierRepeated;

class TypeIdentifierCommaTypeIdentifierRepeatedOptional : public Node {
public:
    TypeIdentifierCommaTypeIdentifierRepeatedOptional() = default;

    TypeIdentifierCommaTypeIdentifierRepeatedOptional(TypeIdentifierCommaTypeIdentifierRepeated* typeIdentifierCommaTypeIdentifierRepeated) :
        typeIdentifierCommaTypeIdentifierRepeated_{typeIdentifierCommaTypeIdentifierRepeated} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::optional<TypeIdentifierCommaTypeIdentifierRepeated*> typeIdentifierCommaTypeIdentifierRepeated_ = {};
};
