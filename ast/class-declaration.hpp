#pragma once

class Identifier;
class ExtendsIdentifierOptional;
class VarDeclarationRepeated;
class MethodDeclarationRepeated;

class ClassDeclaration {
public:
    ClassDeclaration(
        Identifier* className, ExtendsIdentifierOptional* baseClass,
        VarDeclarationRepeated* varDeclarationRepeated,
        MethodDeclarationRepeated* methodDeclarationRepeated) :
            className_{className}, baseClass_{baseClass},
            varDeclarationRepeated_{varDeclarationRepeated},
            methodDeclarationRepeated_{methodDeclarationRepeated} {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    Identifier* className_ = {};
    ExtendsIdentifierOptional* baseClass_ = {};
    VarDeclarationRepeated* varDeclarationRepeated_ = {};
    MethodDeclarationRepeated* methodDeclarationRepeated_ = {};
};
