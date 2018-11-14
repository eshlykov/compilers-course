#pragma once

#include "../visitor.hpp"
#include "expression.hpp"
#include <string>

class UserTypeConstructorExpression : public Expression {
public:
    explicit UserTypeConstructorExpression(const std::string& name) :
        name_{name} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    const std::string name_;
};
