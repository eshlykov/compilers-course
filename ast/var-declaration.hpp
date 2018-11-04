#pragma once

#include "../visitor.hpp"
#include "node.hpp"

class Type;

class VarDeclaration : public Node {
public:
    VarDeclaration(Type* varType, const std::string& varName) :
        varType_{varType}, varName_{varName} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Type* varType_ = {};
    std::string varName_ = {};
};
