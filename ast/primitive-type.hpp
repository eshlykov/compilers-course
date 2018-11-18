#pragma once

#include "../visitor.hpp"
#include "type.hpp"

enum class TypeKind {
    TK_IntArray,
    TK_Boolean,
    TK_Int,
};

class PrimitiveType : public Type {
public:
    explicit PrimitiveType(Location location,
        TypeKind typeKind) :
            typeKind_{typeKind} {
        location_ = location;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    const TypeKind typeKind_;
};
