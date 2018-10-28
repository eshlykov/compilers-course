#pragma once

#include "../visitor.hpp"

class Type;
class Identifier;

class CommaTypeIdentifier {
public:
    CommaTypeIdentifier(Type* type, Identifier* name) :
        type_{type}, name_{name} {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

private:
    Type* type_ = {};
    Identifier* name_ = {};
};
