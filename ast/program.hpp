#pragma once

#include "../visitor.hpp"
#include "node.hpp"
#include <vector>

class MainClass;
class ClassDeclaration;

class Program : public Node {
public:
    Program(MainClass* mainClass, const std::vector<ClassDeclaration*>& classDeclarations) :
        mainClass_{mainClass}, classDeclarations_{classDeclarations} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    MainClass* mainClass_ = {};
    std::vector<ClassDeclaration*> classDeclarations_ = {};
};
