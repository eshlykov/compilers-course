#pragma once

#include "../visitor.hpp"
#include "node.hpp"

class Type;
class Identifier;
class TypeIdentifierCommaTypeIdentifierRepeatedOptional;
class VarDeclarationRepeated;
class StatementRepeated;
class Expression;

class MethodDeclaration : public Node {
public:
    MethodDeclaration(Type* returnType, Identifier* methodName,
        TypeIdentifierCommaTypeIdentifierRepeatedOptional* arguments,
        VarDeclarationRepeated* varDeclarations, StatementRepeated* methodBody,
        Expression* returnExpression) :
            returnType_{returnType}, methodName_{methodName}, arguments_{arguments},
            varDeclarations_{varDeclarations}, methodBody_{methodBody}, returnExpression_{returnExpression} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Type* returnType_ = {};
    Identifier* methodName_ = {};
    TypeIdentifierCommaTypeIdentifierRepeatedOptional* arguments_ = {};
    VarDeclarationRepeated* varDeclarations_ = {};
    StatementRepeated* methodBody_ = {};
    Expression* returnExpression_ = {};
};
