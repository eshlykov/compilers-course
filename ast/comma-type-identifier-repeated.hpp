#pragma once

#include <memory>
#include <vector>

class CommaTypeIdentifier;

class CommaTypeIdentifierRepeated {
public:
    explicit CommaTypeIdentifierRepeated(const std::vector<std::shared_ptr<CommaTypeIdentifier>>& commaTypeIdentifier) :
        commaTypeIdentifier_{commaTypeIdentifier} {
    }

public:
    std::vector<std::shared_ptr<CommaTypeIdentifier>> commaTypeIdentifier_ = {};
};
