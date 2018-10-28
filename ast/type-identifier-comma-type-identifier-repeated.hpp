#pragma once

#include <memory>

class Type;
class Identifier;
class CommaTypeIdentifierRepeated;

class TypeIdentifierCommaTypeIdentifierRepeated {
public:
    TypeIdentifierCommaTypeIdentifierRepeated(Type* type, Identifier* identifier,
        CommaTypeIdentifierRepeated* commaTypeIdenfifierRepeated) :
            type_{type}, identifier_{identifier}, commaTypeIdenfifierRepeated_{commaTypeIdenfifierRepeated} {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    Type* type_= {};
    Identifier* identifier_= {};
    CommaTypeIdentifierRepeated* commaTypeIdenfifierRepeated_ = {};
};
