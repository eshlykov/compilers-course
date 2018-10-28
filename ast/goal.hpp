#pragma once

#include "../visitor.hpp"
#include "node.hpp"

class MainClass;
class ClassDeclarationRepeated;

class Goal : public Node {
public:
    Goal(MainClass* mainClass, ClassDeclarationRepeated* classDeclarationRepeated) :
        mainClass_{mainClass}, classDeclarationRepeated_{classDeclarationRepeated} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    MainClass* mainClass_ = {};
    ClassDeclarationRepeated* classDeclarationRepeated_ = {};
};
