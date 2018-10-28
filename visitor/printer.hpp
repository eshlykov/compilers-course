#pragma once

#include "../ast.hpp"
#include "visitor.hpp"

class Printer : public Visitor {
public:
    virtual void Visit(BracedStatement* node) override {
    }

    virtual void Visit(ClassDeclaration* node) override {
    }

    virtual void Visit(ClassDeclarationRepeated* node) override {
    }

    virtual void Visit(CommaExpression* node) override {
    }

    virtual void Visit(CommaExpressionRepeated* node) override {
    }

    virtual void Visit(CommaTypeIdentifier* node) override {
    }

    virtual void Visit(CommaTypeIdentifierRepeated* node) override {
    }

    virtual void Visit(ExpressionAtExpression* node) override {
    }

    virtual void Visit(ExpressionBang* node) override {
    }

    virtual void Visit(ExpressionBinaryOperatorExpression* node) override {
    }

    virtual void Visit(ExpressionCommaExpressionRepeated* node) override {
    }

    virtual void Visit(ExpressionCommaExpressionRepeatedOptional* node) override {
    }

    virtual void Visit(ExpressionFalse* node) override {
    }

    virtual void Visit(Expression* node) override {
    }

    virtual void Visit(ExpressionIdentifierExpressionCommaExpressionRepeatedOptional* node) override {
    }

    virtual void Visit(ExpressionLength* node) override {
    }

    virtual void Visit(ExpressionNewExpression* node) override {
    }

    virtual void Visit(ExpressionNewIdentifier* node) override {
    }

    virtual void Visit(ExpressionNumber* node) override {
    }

    virtual void Visit(ExpressionParentheses* node) override {
    }

    virtual void Visit(ExpressionThis* node) override {
    }

    virtual void Visit(ExpressionTrue* node) override {
    }

    virtual void Visit(ExtendsIdentifierOptional* node) override {
    }

    virtual void Visit(Goal* node) override {
    }

    virtual void Visit(Identifier* node) override {
    }

    virtual void Visit(MainClass* node) override {
    }

    virtual void Visit(MethodDeclaration* node) override {
    }

    virtual void Visit(MethodDeclarationRepeated* node) override {
    }

    virtual void Visit(Number* node) override {
    }

    virtual void Visit(StatementAssignmentArray* node) override {
    }

    virtual void Visit(StatementAssignment* node) override {
    }

    virtual void Visit(Statement* node) override {
    }

    virtual void Visit(StatementIfElse* node) override {
    }

    virtual void Visit(StatementPrint* node) override {
    }

    virtual void Visit(StatementRepeated* node) override {
    }

    virtual void Visit(StatementWhile* node) override {
    }

    virtual void Visit(TypeBoolean* node) override {
    }

    virtual void Visit(Type* node) override {
    }

    virtual void Visit(TypeIdentifierCommaTypeIdentifierRepeated* node) override {
    }

    virtual void Visit(TypeIdentifierCommaTypeIdentifierRepeatedOptional* node) override {
    }

    virtual void Visit(TypeIdentifier* node) override {
    }

    virtual void Visit(TypeIntArray* node) override {
    }

    virtual void Visit(TypeInt* node) override {
    }

    virtual void Visit(VarDeclaration* node) override {
    }

    virtual void Visit(VarDeclarationRepeated* node) override {
    }
};
