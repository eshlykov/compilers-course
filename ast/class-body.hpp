#pragma once

#include "../visitor.hpp"
#include "node.hpp"

class VarDeclaration;
class MethodDeclaration;

class ClassBody : public Node {
public:
    ClassBody(const std::vector<VarDeclaration*>& variables, const std::vector<MethodDeclaration*>& methods) :
        variables_{variables}, methods_{methods} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visitor(this);
    }

public:
    std::vector<VarDeclaration> variables_ = {};
    std::vector<MethodDeclaration> methods_ = {};
}
