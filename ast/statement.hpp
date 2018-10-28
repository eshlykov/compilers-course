#pragma once

#include "../visitor.hpp"

class Statement {
public:
    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};
