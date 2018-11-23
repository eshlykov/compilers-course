#include "method-call-expression.hpp"

MethodCallExpression::MethodCallExpression(Location location,
    std::unique_ptr<Expression> expression,
    const std::string& methodName,
    std::vector<std::unique_ptr<Expression>>& argumentsList) :
        expression_{std::move(expression)},
        methodName_{methodName},
        argumentsList_{std::move(argumentsList)} {
    location_ = location;
}

void MethodCallExpression::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
