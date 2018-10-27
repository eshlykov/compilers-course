#pragma once

class Identifier;
class ExtendsIdentifierOptional;

class ClassDeclaration {
public:
    ClassDeclaration(Identifier* className, ExtendsIdentifierOptional* baseClass) :
        className_{className}, baseClass_{baseClass} {
    }

public:
    Identifier* className_ = {};
    ExtendsIdentifierOptional* baseClass_ = {};
};
