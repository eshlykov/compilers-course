#pragma once

#include "../visitor.hpp"
#include "node.hpp"

class Identifier;
class ExtendsIdentifierOptional;
class VarDeclarationRepeated;
class MethodDeclarationRepeated;

class ClassDeclaration : public Node {
public:
    ClassDeclaration(
        Identifier* className,
        ExtendsIdentifierOptional* baseClass,
        VarDeclarationRepeated* varDeclarationRepeated,
        MethodDeclarationRepeated* methodDeclarationRepeated) :
        className_{className},
        baseClass_{baseClass},
        varDeclarationRepeated_{varDeclarationRepeated},
        methodDeclarationRepeated_{methodDeclarationRepeated} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Identifier* className_ = {};
    ExtendsIdentifierOptional* baseClass_ = {};
    VarDeclarationRepeated* varDeclarationRepeated_ = {};
    MethodDeclarationRepeated* methodDeclarationRepeated_ = {};
};
