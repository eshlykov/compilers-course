#pragma once

#include <string>

class Identifier {
public:
    Identifier(const std::string& identifier) :
        identifier_(identifier) {
    }

public:
    std::string identifier_;
};
