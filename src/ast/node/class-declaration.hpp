#pragma once

#include "node.hpp"
#include "class-body.hpp"
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace Ast {

    class ClassDeclaration : public Node {
    public:
        ClassDeclaration(Location location,
            const std::string& className,
            std::optional<std::string> extendsForClass,
            std::unique_ptr<ClassBody> classBody);

        void Accept(Visitor* visitor) final;

    public:
        const std::string className_;
        const std::optional<std::string> extendsForClass_;
        const std::unique_ptr<ClassBody> classBody_;
    };

    inline ClassDeclaration::ClassDeclaration(Location location,
        const std::string& className,
        std::optional<std::string> extendsForClass,
        std::unique_ptr<ClassBody> classBody) :
        className_{className},
        extendsForClass_{extendsForClass},
        classBody_{std::move(classBody)} {
        SetLocation(location);
        assert(classBody_ != nullptr);
    }

    inline void ClassDeclaration::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
