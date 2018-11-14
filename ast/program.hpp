#pragma once

#include "../visitor.hpp"
#include "main-class.hpp"
#include "node.hpp"
#include <memory>
#include <vector>

class ClassDeclaration;

class Program : public Node {
public:
    Program(std::unique_ptr<MainClass> mainClass,
        std::vector<std::unique_ptr<ClassDeclaration>>& classDeclarations,
        bool isErroneous) :
            mainClass_{std::move(mainClass)},
            classDeclarations_{std::move(classDeclarations)},
            isErroneous_{isErroneous} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::unique_ptr<MainClass> mainClass_;
    std::vector<std::unique_ptr<ClassDeclaration>> classDeclarations_;
    bool isErroneous_ = false;
};
