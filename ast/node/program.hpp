#pragma once

#include "class-declaration.hpp"
#include "main-class.hpp"
#include "node.hpp"
#include <memory>
#include <vector>

namespace Ast {

    class Program : public Node {
    public:
        Program(Location location,
            std::unique_ptr<MainClass> mainClass,
            std::vector<std::unique_ptr<ClassDeclaration>>& classDeclarations);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const std::unique_ptr<MainClass> mainClass_;
        const std::vector<std::unique_ptr<ClassDeclaration>> classDeclarations_;
    };

}
