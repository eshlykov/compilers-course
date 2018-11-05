#pragma once

#include "../visitor.hpp"
#include "node.hpp"
#include <string>

class Type;
class VarDeclaration;
class MethodBody;

class MethodDeclaration : public Node {
public:
    MethodDeclaration(Type* resultType, const std::string& methodName, const std::vector<VarDeclaration*>& argumentsList, MethodBody* methodBody) :
        resultType_{resultType}, methodName_{methodName}, argumentsList_{argumentsList}, methodBody_{methodBody} {
    }

    ~MethodDeclaration() {
        delete resultType_;
        FreeVector(argumentsList_);
        delete methodBody_;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Type* resultType_ = {};
    std::string methodName_ = {};
    std::vector<VarDeclaration*> argumentsList_ = {};
    MethodBody* methodBody_ = {};
};
