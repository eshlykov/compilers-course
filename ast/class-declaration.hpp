#pragma once

#include "../visitor.hpp"
#include "node.hpp"
#include <vector>

class VarDeclaration;
class MethodDeclaration;

class ClassDeclaration : public Node {
public:
    ClassDeclaration(
        const std::string& className,
        const std::string& extendsForClass,
        const std::vector<VarDeclaration*>& varDeclarations,
        const std::vector<MethodDeclaration*>& methodDeclarations) :
        className_{className},
        extendsForClass_{extendsForClass},
        varDeclarations_{varDeclarations},
        methodDeclarations_{methodDeclarations} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::string className_ = {};
    std::string extendsForClass_ = {};
    std::vector<VarDeclaration*> varDeclarations_ = {};
    std::vector<MethodDeclaration*> methodDeclarations_ = {};
};
