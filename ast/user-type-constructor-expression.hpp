#pragma once

#include "expression.hpp"
#include <string>

class UserTypeConstructorExpression : public Expression {
public:
    explicit UserTypeConstructorExpression(Location location,
        const std::string& name) :
            name_{name} {
        location_ = location;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    const std::string name_;
};
