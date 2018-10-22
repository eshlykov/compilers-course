#pragma once

#include <memory>

class ClassDeclaration;

class VarDeclarationRepeated {
public:
    explicit VarDeclarationRepeated(const std::vector<std::shared_ptr<ClassDeclaration>>& classDeclarationRepeated) :
        classDeclarationRepeated_{classDeclarationRepeated} {
    }

public:
    std::vector<std::shared_ptr<ClassDeclaration>> classDeclarationRepeated_ = {};
};
