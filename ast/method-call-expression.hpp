#pragma once

#include "../visitor.hpp"
#include "expression.hpp"
#include <memory>
#include <string>
#include <vector>

class MethodCallExpression : public Expression {
public:
    MethodCallExpression(std::unique_ptr<Expression> expression,
        const std::string& methodName,
        std::vector<std::unique_ptr<Expression>>& argumentsList) :
            expression_{std::move(expression)},
            methodName_{methodName},
            argumentsList_{std::move(argumentsList)} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::unique_ptr<Expression> expression_;
    const std::string methodName_;
    std::vector<std::unique_ptr<Expression>> argumentsList_;
};
