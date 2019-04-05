#pragma once

#include "method-body.hpp"
#include "var-declaration.hpp"
#include "method-body.hpp"
#include "node.hpp"
#include "type.hpp"
#include <memory>
#include <string>
#include <vector>

namespace Ast {

    class MethodDeclaration : public Node {
    public:
        MethodDeclaration(Location location,
            std::unique_ptr<Type> resultType,
            const std::string& methodName,
            std::vector<std::unique_ptr<VarDeclaration>>& argumentsList,
            std::unique_ptr<MethodBody> methodBody);

        void Accept(Visitor* visitor) final;

    public:
        const std::unique_ptr<Type> resultType_;
        const std::string methodName_;
        const std::vector<std::unique_ptr<VarDeclaration>> argumentsList_;
        const std::unique_ptr<MethodBody> methodBody_;
    };

    inline MethodDeclaration::MethodDeclaration(Location location,
        std::unique_ptr<Type> resultType,
        const std::string& methodName,
        std::vector<std::unique_ptr<VarDeclaration>>& argumentsList,
        std::unique_ptr<MethodBody> methodBody) :
        resultType_{std::move(resultType)},
        methodName_{methodName},
        argumentsList_{std::move(argumentsList)},
        methodBody_{std::move(methodBody)} {
        SetLocation(location);
        assert(resultType_ != nullptr);
        assert(methodBody_ != nullptr);
    }


    inline void MethodDeclaration::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
