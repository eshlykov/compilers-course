#pragma once

#include "../visitor.hpp"
#include "node.hpp"
#include <memory>
#include <optional>
#include <string>
#include <vector>

class ClassBody;

class ClassDeclaration : public Node {
public:
    ClassDeclaration(const std::string& className,
        std::optional<std::string> extendsForClass,
        std::unique_ptr<ClassBody> classBody) :
            className_{className},
            extendsForClass_{extendsForClass},
            classBody_{std::move(classBody)} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    const std::string className_;
    std::optional<std::string> extendsForClass_;
    std::unique_ptr<ClassBody> classBody_;
};
