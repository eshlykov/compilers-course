#include "program.hpp"

Program::Program(Location location,
    std::unique_ptr<MainClass> mainClass,
    std::vector<std::unique_ptr<ClassDeclaration>>& classDeclarations) :
        mainClass_{std::move(mainClass)},
        classDeclarations_{std::move(classDeclarations)} {
    location_ = location;
}

void Program::Accept(Visitor* visitor) {
    visitor->Visit(this);
}