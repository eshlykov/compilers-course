#pragma once

#include <memory>

class Type;
class Identifier;
class CommaTypeIdentifierRepeated;

class TypeIdentifierCommaTypeIdentifierRepeated {
public:
    TypeIdentifierCommaTypeIdentifierRepeated(std::shared_ptr<Type> type, std::shared_ptr<Identifier> identifier,
        std::shared_ptr<CommaTypeIdentifierRepeated> commaTypeIdenfifierRepeated) :
            type_{type}, identifier_{identifier}, commaTypeIdenfifierRepeated_{commaTypeIdenfifierRepeated} {
    }

public:
    std::shared_ptr<Type> type_= {};
    std::shared_ptr<Identifier> identifier_= {};
    std::shared_ptr<CommaTypeIdentifierRepeated> commaTypeIdenfifierRepeated_ = {};
};
