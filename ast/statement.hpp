#pragma once

class Statement {
public:
    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }
};
