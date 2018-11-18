#pragma once

#include "../location.hpp"

enum class TypeKind {
	TK_Undefined,
    TK_IntArray,
    TK_Boolean,
    TK_Int,
};

class Visitor;

class Node {
public:
    virtual ~Node() = default;

    virtual void Accept(Visitor*) = 0;

public:
    Location location_;
};
