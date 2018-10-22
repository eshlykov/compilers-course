#pragma once

#include <memory>
#include <optional>

class TypeIdentifierCommaTypeIdentifierRepeated;

class TypeIdentifierCommaTypeIdentifierRepeatedOptional {
public:
    TypeIdentifierCommaTypeIdentifierRepeatedOptional(std::optional<std::shared_ptr<TypeIdentifierCommaTypeIdentifierRepeated>> typeIdentifierCommaTypeIdentifierRepeated) :
        typeIdentifierCommaTypeIdentifierRepeated_{typeIdentifierCommaTypeIdentifierRepeated} {
    }

public:
    std::optional<std::shared_ptr<TypeIdentifierCommaTypeIdentifierRepeated>> typeIdentifierCommaTypeIdentifierRepeated_ = {};
};
