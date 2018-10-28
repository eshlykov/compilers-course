#pragma once

#include "../visitor.hpp"
#include "node.hpp"
#include <memory>

class Type;
class Identifier;
class CommaTypeIdentifierRepeated;

class TypeIdentifierCommaTypeIdentifierRepeated : public Node {
public:
    TypeIdentifierCommaTypeIdentifierRepeated(Type* type, Identifier* identifier,
        CommaTypeIdentifierRepeated* commaTypeIdenfifierRepeated) :
            type_{type}, identifier_{identifier}, commaTypeIdenfifierRepeated_{commaTypeIdenfifierRepeated} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Type* type_= {};
    Identifier* identifier_= {};
    CommaTypeIdentifierRepeated* commaTypeIdenfifierRepeated_ = {};
};
