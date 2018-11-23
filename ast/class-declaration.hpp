#pragma once

#include "node.hpp"
#include "class-body.hpp"
#include <memory>
#include <optional>
#include <string>
#include <vector>

class ClassDeclaration : public Node {
public:
    ClassDeclaration(Location location,
        const std::string& className,
        std::optional<std::string> extendsForClass,
        std::unique_ptr<ClassBody> classBody) :
            className_{className},
            extendsForClass_{extendsForClass},
            classBody_{std::move(classBody)} {
        location_ = location;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    const std::string className_;
    std::optional<std::string> extendsForClass_;
    std::unique_ptr<ClassBody> classBody_;
};
