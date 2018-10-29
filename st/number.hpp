#pragma once

#include "../visitor.hpp"
#include "expression.hpp"

class Number : public Expression {
public:
    Number(int number) :
        number_(number) {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    int number_;
};
