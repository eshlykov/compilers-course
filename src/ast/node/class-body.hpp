#pragma once

#include "node.hpp"
#include "var-declaration.hpp"
#include "method-declaration.hpp"
#include <memory>
#include <vector>

namespace Ast {

    class ClassBody : public Node {
    public:
        ClassBody(Location location,
            std::vector<std::unique_ptr<VarDeclaration>>& variables,
            std::vector<std::unique_ptr<MethodDeclaration>>& methods);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const std::vector<std::unique_ptr<VarDeclaration>> variables_;
        const std::vector<std::unique_ptr<MethodDeclaration>> methods_;
    };

}
