#pragma once

#include <memory>

class Identifier;
class ExtendsIdentifierOptional;

class ClassDeclaration {
public:
    ClassDeclaration(std::shared_ptr<Identifier> className, std::shared_ptr<ExtendsIdentifierOptional> baseClass) :
        className_{className}, baseClass_{baseClass} {
    }

public:
    std::shared_ptr<Identifier> className_ = {};
    std::shared_ptr<ExtendsIdentifierOptional> baseClass_ = {};
};
