#pragma once

#include "../../ast.hpp"
#include "../visitor.hpp"
#include <fstream>
#include <optional>
#include <string>
#include <vector>

class Printer : public Visitor {
public:
    Printer(const std::string& filename);

    ~Printer();

    virtual void Visit(AssignmentByIndexStatement* node) override final;

    virtual void Visit(AssignmentStatement* node) override final;

    virtual void Visit(BinaryOperatorExpression* node) override final;

    virtual void Visit(BooleanExpression* node) override final;

    virtual void Visit(ClassBody* node) override final;

    virtual void Visit(ClassDeclaration* node) override final;

    virtual void Visit(ConditionStatement* node) override final;

    virtual void Visit(IdentifierExpression* node) override final;

    virtual void Visit(IndexExpression* node) override final;

    virtual void Visit(IntArrayConstructorExpression* node) override final;

    virtual void Visit(LengthExpression* node) override final;

    virtual void Visit(LoopStatement* node) override final;

    virtual void Visit(MainClass* node) override final;

    virtual void Visit(MethodBody* node) override final;

    virtual void Visit(MethodCallExpression* node) override final;

    virtual void Visit(MethodDeclaration* node) override final;

    virtual void Visit(NotExpression* node) override final;

    virtual void Visit(NumberExpression* node) override final;

    virtual void Visit(PrintStatement* node) override final;

    virtual void Visit(Program* node) override final;

    virtual void Visit(ScopeStatement* node) override final;

    virtual void Visit(ThisExpression* node) override final;

    virtual void Visit(Type* node) override final;

    virtual void Visit(UserTypeConstructorExpression* node) override final;

    virtual void Visit(VarDeclaration* node) override final;

private:
    void PrintHead(int headNodeNumber, const std::string& label);

    void PrintEdge(int headNodeNumber);

    void PrintLeaf(int headNodeNumber, const std::string& label, const std::string& name);

private:
    std::ofstream file_;
    int nodeNumber_;
};
