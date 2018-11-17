#pragma once

class Visitor;

class Node {
public:
    virtual ~Node() = default;

    virtual void Accept(Visitor*) = 0;
};
