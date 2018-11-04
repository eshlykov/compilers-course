#pragma once

#include "../visitor.hpp"
#include "node.hpp"

class Type;

class VarDeclaration : public Node {
public:
    VarDeclaration(Type* type, const std::string& name) :
        type_{type}, name_{name} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Type* type_ = {};
    std::string name_ = {};
};
