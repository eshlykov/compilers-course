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
    explicit PrimitiveType(TypeKind typeKind) :
        typeKind_{typeKind} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    TypeKind typeKind_ = {};
};
