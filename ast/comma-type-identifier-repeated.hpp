#pragma once

#include "../visitor.hpp"
#include "node.hpp"
#include <vector>

class CommaTypeIdentifier;

class CommaTypeIdentifierRepeated : public Node {
public:
    CommaTypeIdentifierRepeated() = default;

    CommaTypeIdentifierRepeated(const std::vector<CommaTypeIdentifier*>& commaTypeIdentifierRepeated) :
        commaTypeIdentifierRepeated_{commaTypeIdentifierRepeated} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::vector<CommaTypeIdentifier*> commaTypeIdentifierRepeated_ = {};
};
