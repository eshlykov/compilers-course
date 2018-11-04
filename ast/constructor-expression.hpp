#pragma once

#include "../visitor.hpp"
#include "expression.hpp"
#include <string>

class ConstructorExpression : public Expression {
public:
    ConstructorExpression(const std::string& name) :
        name_{name} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::string name_ = {};
};
