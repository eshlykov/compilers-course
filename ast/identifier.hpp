#pragma once

#include "../visitor.hpp"
#include "expression.hpp"
#include <string>

class Identifier : public Expression {
public:
    Identifier(const std::string& identifier) :
        identifier_(identifier) {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::string identifier_;
};
