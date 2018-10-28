#pragma once

#include "../visitor.hpp"
#include "node.hpp"
#include <vector>

class ClassDeclaration;

class ClassDeclarationRepeated : public Node {
public:
    ClassDeclarationRepeated() = default;

    ClassDeclarationRepeated(const std::vector<ClassDeclaration*>& classDeclarationRepeated) :
        classDeclarationRepeated_{classDeclarationRepeated} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::vector<ClassDeclaration*> classDeclarationRepeated_ = {};
};
