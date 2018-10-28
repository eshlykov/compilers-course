#pragma once

#include "../visitor.hpp"
#include "node.hpp"

class VarDeclaration;

class VarDeclarationRepeated : public Node {
public:
    VarDeclarationRepeated() = default;

    VarDeclarationRepeated(const std::vector<VarDeclaration*>& varDeclarationRepeated) :
        varDeclarationRepeated_{varDeclarationRepeated} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::vector<VarDeclaration*> varDeclarationRepeated_ = {};
};
