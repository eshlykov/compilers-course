#pragma once

class Expression {
public:
    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};
