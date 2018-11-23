#pragma once

#include "main-class.hpp"
#include "class-declaration.hpp"
#include "node.hpp"
#include <memory>
#include <vector>


class Program : public Node {
public:
    Program(Location location,
        std::unique_ptr<MainClass> mainClass,
        std::vector<std::unique_ptr<ClassDeclaration>>& classDeclarations);

    virtual void Accept(Visitor* visitor) override final;

public:
    std::unique_ptr<MainClass> mainClass_;
    std::vector<std::unique_ptr<ClassDeclaration>> classDeclarations_;
};
