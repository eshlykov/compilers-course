#pragma once

#include "../visitor.hpp"
#include "expression.hpp"
#include <string>
#include <vector>

class MethodCallExpression : public Expression {
public:
    MethodCallExpression(Expression* expression, const std::string& methodName, const std::vector<Expression*>& argumentsList) :
        expression_{expression}, methodName_{methodName}, argumentsList_{argumentsList} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Expression* expression_ = {};
    std::string methodName_ = {};
    std::vector<Expression*> argumentsList_ = {};
};
