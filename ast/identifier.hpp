#pragma once

#include "expression.hpp"
#include <string>

class Identifier : public Expression {
public:
    Identifier(const std::string& identifier) :
        identifier_(identifier) {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    std::string identifier_;
};
