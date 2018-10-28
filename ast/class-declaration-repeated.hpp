#pragma once

#include <vector>

class ClassDeclaration;

class ClassDeclarationRepeated {
public:
    ClassDeclarationRepeated() = default;

    ClassDeclarationRepeated(const std::vector<ClassDeclaration*>& classDeclarationRepeated) :
        classDeclarationRepeated_{classDeclarationRepeated} {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    std::vector<ClassDeclaration*> classDeclarationRepeated_ = {};
};
