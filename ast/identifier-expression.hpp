#pragma once

#include "expression.hpp"
#include <string>

class IdentifierExpression : public Expression {
public:
    IdentifierExpression(Location location,
        const std::string& name);


    virtual void Accept(Visitor* visitor) override final;

public:
    const std::string name_;
};
