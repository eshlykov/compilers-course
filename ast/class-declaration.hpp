#pragma once

#include "../visitor.hpp"
#include "node.hpp"
#include <optional>
#include <string>
#include <vector>

class ClassBody;

class ClassDeclaration : public Node {
public:
    ClassDeclaration(
        const std::string& className, std::optional<std::string> extendsForClass, ClassBody* classBody) :
        className_{className}, extendsForClass_{extendsForClass}, classBody_{classBody} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::string className_ = {};
    std::optional<std::string> extendsForClass_ = {};
    ClassBody* classBody_ = {};
};
