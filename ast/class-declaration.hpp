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
        std::unique_ptr<ClassBody> classBody);

    virtual void Accept(Visitor* visitor) override final;

public:
    const std::string className_;
    std::optional<std::string> extendsForClass_;
    std::unique_ptr<ClassBody> classBody_;
};
