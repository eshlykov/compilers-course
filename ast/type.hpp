#pragma once

#include "node.hpp"
#include <string>
#include <variant>

class Type : public Node {
public:
    Type(Location location, const std::string& className);

    Type(Location location, TypeKind typeKind);

    virtual void Accept(Visitor* visitor) override final;

public:
    std::variant<TypeKind, std::string> type_;
};
