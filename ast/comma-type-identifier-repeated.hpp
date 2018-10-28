#pragma once

#include <vector>

class CommaTypeIdentifier;

class CommaTypeIdentifierRepeated {
public:
    CommaTypeIdentifierRepeated() = default;

    CommaTypeIdentifierRepeated(const std::vector<CommaTypeIdentifier*>& commaTypeIdentifierRepeated) :
        commaTypeIdentifierRepeated_{commaTypeIdentifierRepeated} {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    std::vector<CommaTypeIdentifier*> commaTypeIdentifierRepeated_ = {};
};
