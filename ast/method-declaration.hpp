#pragma once

#include "method-body.hpp"
#include "var-declaration.hpp"
#include "method-body.hpp"
#include "node.hpp"
#include "type.hpp"
#include <memory>
#include <string>
#include <vector>

class MethodDeclaration : public Node {
public:
    MethodDeclaration(Location location,
        std::unique_ptr<Type> resultType,
        const std::string& methodName,
        std::vector<std::unique_ptr<VarDeclaration>>& argumentsList,
        std::unique_ptr<MethodBody> methodBody);

    virtual void Accept(Visitor* visitor) override final;

public:
    std::unique_ptr<Type> resultType_;
    const std::string methodName_;
    std::vector<std::unique_ptr<VarDeclaration>> argumentsList_;
    std::unique_ptr<MethodBody> methodBody_;
};
