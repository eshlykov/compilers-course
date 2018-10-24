#pragma once

#include <memory>

class MainClass;
class ClassDeclarationRepeated;

class Goal {
public:
    Goal(std::shared_ptr<MainClass> mainClass, std::shared_ptr<ClassDeclarationRepeated> classDeclarationRepeated) :
        mainClass_{mainClass}, classDeclarationRepeated_{classDeclarationRepeated} {
    }

public:
    std::shared_ptr<MainClass> mainClass_ = {};
    std::shared_ptr<ClassDeclarationRepeated> classDeclarationRepeated_ = {};
};
