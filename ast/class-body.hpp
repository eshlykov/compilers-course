#pragma once

#include "node.hpp"
#include "var-declaration.hpp"
#include "method-declaration.hpp"
#include <memory>
#include <vector>

class ClassBody : public Node {
public:
    ClassBody(Location location,
        std::vector<std::unique_ptr<VarDeclaration>>& variables,
        std::vector<std::unique_ptr<MethodDeclaration>>& methods) :
            variables_{std::move(variables)},
            methods_{std::move(methods)} {
        location_ = location;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::vector<std::unique_ptr<VarDeclaration>> variables_;
    std::vector<std::unique_ptr<MethodDeclaration>> methods_;
};
