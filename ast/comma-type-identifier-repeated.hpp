#pragma once

#include <vector>

class CommaTypeIdentifier;

class CommaTypeIdentifierRepeated {
public:
    explicit CommaTypeIdentifierRepeated(const std::vector<CommaTypeIdentifier*>& commaTypeIdentifier) :
        commaTypeIdentifier_{commaTypeIdentifier} {
    }

public:
    std::vector<CommaTypeIdentifier*> commaTypeIdentifier_ = {};
};
