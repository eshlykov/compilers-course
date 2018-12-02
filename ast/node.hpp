#pragma once

#include "../utils/location.hpp"
#include "../utils/visitor.hpp"

enum class TypeKind {
    TK_Undefined,
    TK_IntArray,
    TK_Boolean,
    TK_Int,
};

class Node {
public:
    virtual ~Node() = default;

    virtual void Accept(Visitor*) = 0;

    void SetLocation(const Location& location);

    Location GetLocation() const;

private:
    Location location_;
};
