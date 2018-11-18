#pragma once

#include "main-class.hpp"
#include "node.hpp"
#include <memory>
#include <vector>

class ClassDeclaration;

class Program : public Node {
public:
    Program(Location location,
        std::unique_ptr<MainClass> mainClass,
        std::vector<std::unique_ptr<ClassDeclaration>>& classDeclarations) :
            mainClass_{std::move(mainClass)},
            classDeclarations_{std::move(classDeclarations)} {
        location_ = location;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::unique_ptr<MainClass> mainClass_;
    std::vector<std::unique_ptr<ClassDeclaration>> classDeclarations_;
};
