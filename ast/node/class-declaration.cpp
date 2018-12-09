#include "class-declaration.hpp"

ClassDeclaration::ClassDeclaration(Location location,
    const std::string& className,
    std::optional<std::string> extendsForClass,
    std::unique_ptr<ClassBody> classBody) :
        className_{className},
        extendsForClass_{extendsForClass},
        classBody_{std::move(classBody)} {
    SetLocation(location);
    assert(classBody_ != nullptr);
}

void ClassDeclaration::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
