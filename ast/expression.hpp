#pragma once

#include "../visitor.hpp"

class Expression {
public:
    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};
