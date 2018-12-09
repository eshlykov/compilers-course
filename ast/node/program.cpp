#include "program.hpp"

namespace Ast {

    Program::Program(Location location,
        std::unique_ptr<MainClass> mainClass,
        std::vector<std::unique_ptr<ClassDeclaration>>& classDeclarations) :
            mainClass_{std::move(mainClass)},
            classDeclarations_{std::move(classDeclarations)} {
        SetLocation(location);
        assert(mainClass_ != nullptr);
    }

    void Program::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
