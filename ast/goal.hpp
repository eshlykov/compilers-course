#pragma once

#include "../visitor.hpp"

class MainClass;
class ClassDeclarationRepeated;

class Goal {
public:
    Goal(MainClass* mainClass, ClassDeclarationRepeated* classDeclarationRepeated) :
        mainClass_{mainClass}, classDeclarationRepeated_{classDeclarationRepeated} {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    MainClass* mainClass_ = {};
    ClassDeclarationRepeated* classDeclarationRepeated_ = {};
};
