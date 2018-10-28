#pragma once

#include "../visitor.hpp"
#include "node.hpp"

class Type;
class Identifier;

class VarDeclaration : public Node {
public:
    VarDeclaration(Type* type, Identifier* varName) :
        type_{type}, varName_{varName} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Type* type_ = {};
    Identifier* varName_ = {};
};
