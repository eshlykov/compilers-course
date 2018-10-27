#pragma once

#include "expression.hpp"
#include <string>

class Identifier : public Expression {
public:
    Identifier(const std::string& identifier) :
        identifier_(identifier) {
    }

public:
    std::string identifier_;
};
