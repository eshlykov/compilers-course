#pragma once

#include <vector>

class CommaTypeIdentifier;

class CommaTypeIdentifierRepeated {
public:
    explicit CommaTypeIdentifierRepeated(const std::vector<CommaTypeIdentifier*>& commaTypeIdentifierRepeated) :
        commaTypeIdentifierRepeated_{commaTypeIdentifierRepeated} {
    }

public:
    std::vector<CommaTypeIdentifier*> commaTypeIdentifierRepeated_ = {};
};
