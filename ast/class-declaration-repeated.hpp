#pragma once

#include <memory>
#include <vector>

class ClassDeclaration;

class ClassDeclarationRepeated {
public:
    ClassDeclarationRepeated(const std::vector<std::shared_ptr<ClassDeclaration>> classDeclarationRepeated) :
        classDeclarationRepeated_{classDeclarationRepeated} {
    }

public:
    std::vector<std::shared_ptr<ClassDeclaration>> classDeclarationRepeated_ = {};
};
