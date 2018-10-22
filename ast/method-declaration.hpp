#pragma once

class Type;
class Identifier;
class TypeIdentifierCommaTypeIdentifierRepeatedOptional;
class VarDeclarationRepeated;
class StatementRepeated;
class Expression;

class MethodDeclaration {
public:
    MethodDeclaration(std::shared_ptr<Type> returnType, std::shared_ptr<Identifier> methodName,
        std::shared_ptr<TypeIdentifierCommaTypeIdentifierRepeatedOptional> arguments,
        std::shared_ptr<VarDeclarationRepeated> varDeclarations, std::shared_ptr<StatementRepeated> methodBody,
        std::shared_ptr<Expression> returnExpression) :
            returnType_{returnType}, methodName_{methodName}, arguments_{arguments},
            varDeclarations_{varDeclarations}, methodBody_{methodBody}, returnExpression_{returnExpression} {
    }

public:
    std::shared_ptr<Type> returnType_ = {};
    std::shared_ptr<Identifier> methodName_ = {};
    std::shared_ptr<TypeIdentifierCommaTypeIdentifierRepeatedOptional> arguments_ = {};
    std::shared_ptr<VarDeclarationRepeated> varDeclarations_ = {};
    std::shared_ptr<StatementRepeated> methodBody_ = {};
    std::shared_ptr<Expression> returnExpression_ = {};
};
