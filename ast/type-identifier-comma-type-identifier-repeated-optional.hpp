#pragma once

#include "../visitor.hpp"
#include <optional>

class TypeIdentifierCommaTypeIdentifierRepeated;

class TypeIdentifierCommaTypeIdentifierRepeatedOptional {
public:
    TypeIdentifierCommaTypeIdentifierRepeatedOptional() = default;

    TypeIdentifierCommaTypeIdentifierRepeatedOptional(TypeIdentifierCommaTypeIdentifierRepeated* typeIdentifierCommaTypeIdentifierRepeated) :
        typeIdentifierCommaTypeIdentifierRepeated_{typeIdentifierCommaTypeIdentifierRepeated} {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    std::optional<TypeIdentifierCommaTypeIdentifierRepeated*> typeIdentifierCommaTypeIdentifierRepeated_ = {};
};
