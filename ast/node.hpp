#pragma once

#include "../location.hpp"

class Visitor;

class Node {
public:
    virtual ~Node() = default;

    virtual void Accept(Visitor*) = 0;

public:
    Location location_;
};
