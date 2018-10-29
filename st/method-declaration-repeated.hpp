#pragma once

#include "../visitor.hpp"
#include "node.hpp"

class MethodDeclaration;

class MethodDeclarationRepeated : public Node {
public:
    MethodDeclarationRepeated() = default;

    explicit MethodDeclarationRepeated(const std::vector<MethodDeclaration*>& methodDeclarationRepeated) :
        methodDeclarationRepeated_{methodDeclarationRepeated} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::vector<MethodDeclaration*> methodDeclarationRepeated_ = {};
};
