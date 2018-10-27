#pragma once

#include <optional>

class TypeIdentifierCommaTypeIdentifierRepeated;

class TypeIdentifierCommaTypeIdentifierRepeatedOptional {
public:
    TypeIdentifierCommaTypeIdentifierRepeatedOptional(TypeIdentifierCommaTypeIdentifierRepeated* typeIdentifierCommaTypeIdentifierRepeated) :
        typeIdentifierCommaTypeIdentifierRepeated_{typeIdentifierCommaTypeIdentifierRepeated} {
    }

public:
    std::optional<TypeIdentifierCommaTypeIdentifierRepeated*> typeIdentifierCommaTypeIdentifierRepeated_ = {};
};
