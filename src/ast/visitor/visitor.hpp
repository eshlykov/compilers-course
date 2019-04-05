#pragma once

namespace Ast {

    class AssignmentByIndexStatement;
    class AssignmentStatement;
    class BinaryOperatorExpression;
    class BooleanExpression;
    class ClassBody;
    class ClassDeclaration;
    class ConditionStatement;
    class IdentifierExpression;
    class IndexExpression;
    class IntArrayConstructorExpression;
    class LengthExpression;
    class LoopStatement;
    class MainClass;
    class MethodBody;
    class MethodCallExpression;
    class MethodDeclaration;
    class NotExpression;
    class NumberExpression;
    class PrintStatement;
    class Program;
    class ScopeStatement;
    class ThisExpression;
    class Type;
    class UserTypeConstructorExpression;
    class VarDeclaration;

    class Visitor {
    public:
        virtual void Visit(AssignmentByIndexStatement*) = 0;
        virtual void Visit(AssignmentStatement*) = 0;
        virtual void Visit(BinaryOperatorExpression*) = 0;
        virtual void Visit(BooleanExpression*) = 0;
        virtual void Visit(ClassBody*) = 0;
        virtual void Visit(ClassDeclaration*) = 0;
        virtual void Visit(ConditionStatement*) = 0;
        virtual void Visit(IdentifierExpression*) = 0;
        virtual void Visit(IndexExpression*) = 0;
        virtual void Visit(IntArrayConstructorExpression*) = 0;
        virtual void Visit(LengthExpression*) = 0;
        virtual void Visit(LoopStatement*) = 0;
        virtual void Visit(MainClass*) = 0;
        virtual void Visit(MethodBody*) = 0;
        virtual void Visit(MethodCallExpression*) = 0;
        virtual void Visit(MethodDeclaration*) = 0;
        virtual void Visit(NotExpression*) = 0;
        virtual void Visit(NumberExpression*) = 0;
        virtual void Visit(PrintStatement*) = 0;
        virtual void Visit(Program*) = 0;
        virtual void Visit(ScopeStatement*) = 0;
        virtual void Visit(ThisExpression*) = 0;
        virtual void Visit(Type*) = 0;
        virtual void Visit(UserTypeConstructorExpression*) = 0;
        virtual void Visit(VarDeclaration*) = 0;
    };

}
