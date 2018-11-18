#pragma once

#include "../visitor.hpp"
#include "expression.hpp"
#include <string>

class IdentifierExpression : public Expression {
public:
    IdentifierExpression(Location location,
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
