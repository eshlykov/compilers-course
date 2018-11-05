#pragma once

#include "common.hpp"

class Visitor;

class Node {
public:
    virtual ~Node() = default;

    virtual void Accept(Visitor*) = 0;
};
