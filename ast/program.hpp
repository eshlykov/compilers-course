#pragma once

#include "../visitor.hpp"
#include "main-class.hpp"
#include "node.hpp"
#include <vector>

class ClassDeclaration;

class Program : public Node {
public:
    Program(MainClass* mainClass,
        const std::vector<ClassDeclaration*>& classDeclarations,
        bool isErroneous) :
            mainClass_{mainClass},
            classDeclarations_{classDeclarations},
            isErroneous_{isErroneous} {
    }

    ~Program() {
        delete mainClass_;
        FreeVector(classDeclarations_);
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    MainClass* mainClass_;
    std::vector<ClassDeclaration*> classDeclarations_;
    bool isErroneous_ = false;
};
