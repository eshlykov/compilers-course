#pragma once

class BracedStatement;
class ClassDeclaration;
class ClassDeclarationRepeated;
class CommaExpression;
class CommaExpressionRepeated;
class CommaTypeIdentifier;
class CommaTypeIdentifierRepeated;
class ExpressionAtExpression;
class ExpressionBang;
class ExpressionBinaryOperatorExpression;
class ExpressionCommaExpressionRepeated;
class ExpressionCommaExpressionRepeatedOptional;
class ExpressionFalse;
class Expression;
class ExpressionIdentifierExpressionCommaExpressionRepeatedOptional;
class ExpressionLength;
class ExpressionNewExpression;
class ExpressionNewIdentifier;
class ExpressionNumber;
class ExpressionParentheses;
class ExpressionThis;
class ExpressionTrue;
class ExtendsIdentifierOptional;
class Goal;
class Identifier;
class MainClass;
class MethodDeclaration;
class MethodDeclarationRepeated;
class Number;
class StatementAssignmentArray;
class StatementAssignment;
class Statement;
class StatementIfElse;
class StatementPrint;
class StatementRepeated;
class StatementWhile;
class TypeBoolean;
class Type;
class TypeIdentifierCommaTypeIdentifierRepeated;
class TypeIdentifierCommaTypeIdentifierRepeatedOptional;
class TypeIdentifier;
class TypeIntArray;
class TypeInt;
class VarDeclaration;
class VarDeclarationRepeated;

class Visitor {
public:
    virtual void Visit(BracedStatement* node) = 0;
    virtual void Visit(ClassDeclaration* node) = 0;
    virtual void Visit(ClassDeclarationRepeated* node) = 0;
    virtual void Visit(CommaExpression* node) = 0;
    virtual void Visit(CommaExpressionRepeated* node) = 0;
    virtual void Visit(CommaTypeIdentifier* node) = 0;
    virtual void Visit(CommaTypeIdentifierRepeated* node) = 0;
    virtual void Visit(ExpressionAtExpression* node) = 0;
    virtual void Visit(ExpressionBang* node) = 0;
    virtual void Visit(ExpressionBinaryOperatorExpression* node) = 0;
    virtual void Visit(ExpressionCommaExpressionRepeated* node) = 0;
    virtual void Visit(ExpressionCommaExpressionRepeatedOptional* node) = 0;
    virtual void Visit(ExpressionFalse* node) = 0;
    virtual void Visit(Expression* node) = 0;
    virtual void Visit(ExpressionIdentifierExpressionCommaExpressionRepeatedOptional* node) = 0;
    virtual void Visit(ExpressionLength* node) = 0;
    virtual void Visit(ExpressionNewExpression* node) = 0;
    virtual void Visit(ExpressionNewIdentifier* node) = 0;
    virtual void Visit(ExpressionNumber* node) = 0;
    virtual void Visit(ExpressionParentheses* node) = 0;
    virtual void Visit(ExpressionThis* node) = 0;
    virtual void Visit(ExpressionTrue* node) = 0;
    virtual void Visit(ExtendsIdentifierOptional* node) = 0;
    virtual void Visit(Goal* node) = 0;
    virtual void Visit(Identifier* node) = 0;
    virtual void Visit(MainClass* node) = 0;
    virtual void Visit(MethodDeclaration* node) = 0;
    virtual void Visit(MethodDeclarationRepeated* node) = 0;
    virtual void Visit(Number* node) = 0;
    virtual void Visit(StatementAssignmentArray* node) = 0;
    virtual void Visit(StatementAssignment* node) = 0;
    virtual void Visit(Statement* node) = 0;
    virtual void Visit(StatementIfElse* node) = 0;
    virtual void Visit(StatementPrint* node) = 0;
    virtual void Visit(StatementRepeated* node) = 0;
    virtual void Visit(StatementWhile* node) = 0;
    virtual void Visit(TypeBoolean* node) = 0;
    virtual void Visit(Type* node) = 0;
    virtual void Visit(TypeIdentifierCommaTypeIdentifierRepeated* node) = 0;
    virtual void Visit(TypeIdentifierCommaTypeIdentifierRepeatedOptional* node) = 0;
    virtual void Visit(TypeIdentifier* node) = 0;
    virtual void Visit(TypeIntArray* node) = 0;
    virtual void Visit(TypeInt* node) = 0;
    virtual void Visit(VarDeclaration* node) = 0;
    virtual void Visit(VarDeclarationRepeated* node) = 0;
};