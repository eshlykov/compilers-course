#pragma once

#include "../visitor.hpp"
#include "method-body.hpp"
#include "node.hpp"
#include "type.hpp"
#include <memory>
#include <string>

class VarDeclaration;

class MethodDeclaration : public Node {
public:
    MethodDeclaration(std::unique_ptr<Type> resultType,
        const std::string& methodName,
        std::vector<std::unique_ptr<VarDeclaration>>& argumentsList,
        std::unique_ptr<MethodBody> methodBody) :
            resultType_{std::move(resultType)},
            methodName_{methodName},
            argumentsList_{std::move(argumentsList)},
            methodBody_{std::move(methodBody)} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::unique_ptr<Type> resultType_;
    const std::string methodName_;
    std::vector<std::unique_ptr<VarDeclaration>> argumentsList_;
    std::unique_ptr<MethodBody> methodBody_;
};
