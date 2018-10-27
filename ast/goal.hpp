#pragma once

class MainClass;
class ClassDeclarationRepeated;

class Goal {
public:
    Goal(MainClass* mainClass, ClassDeclarationRepeated* classDeclarationRepeated) :
        mainClass_{mainClass}, classDeclarationRepeated_{classDeclarationRepeated} {
    }

public:
    MainClass* mainClass_ = {};
    ClassDeclarationRepeated* classDeclarationRepeated_ = {};
};
