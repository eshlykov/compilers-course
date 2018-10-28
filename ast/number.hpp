#pragma once

class Number {
public:
    Number(int number) :
        number_(number) {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    int number_;
};
