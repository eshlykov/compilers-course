#pragma once

#include "../visitor.hpp"
#include "node.hpp"

class Type;
class Identifier;

class CommaTypeIdentifier : public Node {
public:
    CommaTypeIdentifier(Type* type, Identifier* name) :
        type_{type}, name_{name} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Type* type_ = {};
    Identifier* name_ = {};
};
