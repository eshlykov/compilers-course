#include "method-declaration.hpp"

MethodDeclaration::MethodDeclaration(Location location,
    std::unique_ptr<Type> resultType,
    const std::string& methodName,
    std::vector<std::unique_ptr<VarDeclaration>>& argumentsList,
    std::unique_ptr<MethodBody> methodBody) :
        resultType_{std::move(resultType)},
        methodName_{methodName},
        argumentsList_{std::move(argumentsList)},
        methodBody_{std::move(methodBody)} {
    location_ = location;
}


void MethodDeclaration::Accept(Visitor* visitor) override final {
    visitor->Visit(this);
}
