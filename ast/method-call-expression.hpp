#pragma once

#include "../visitor.hpp"
#include "expression.hpp"
#include "string"
#include "vector"

class MethodCallExpression : public Expression {
public:
    MethodCallExpression(Expression* expression, const std::string& method, const std::vector<Expression*>& arguments) :
        expression_{expression}, method_{method}, arguments_{arguments} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Expression* expression_ = {};
    std::string method_ = {};
    std::vector<Expression*> arguments_ = {};
};
