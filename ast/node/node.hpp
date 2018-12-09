#pragma once

#include "../../utils/location.hpp"
#include "../visitor/visitor.hpp"
#include <cassert>

enum class TypeKind {
    Undefined,
    IntArray,
    Boolean,
    Int,
};

class Node {
public:
    Node() = default;

    virtual ~Node() = default;

    virtual void Accept(Visitor*) = 0;

    void SetLocation(const Location& location);

    const Location& GetLocation() const;

private:
    Location location_;
};
