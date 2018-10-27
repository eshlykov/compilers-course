#pragma once

#include <vector>

class ClassDeclaration;

class ClassDeclarationRepeated {
public:
    ClassDeclarationRepeated() = default;

    ClassDeclarationRepeated(const std::vector<ClassDeclaration*>& classDeclarationRepeated) :
        classDeclarationRepeated_{classDeclarationRepeated} {
    }

public:
    std::vector<ClassDeclaration*> classDeclarationRepeated_ = {};
};
