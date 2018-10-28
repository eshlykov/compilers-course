#pragma once

#include "../ast.hpp"
#include "visitor.hpp"
#include <fstream>

class Printer : public Visitor {
public:
    Printer(const std::string& filename) :
        file_{filename}, nodeNumber_{0} {
            file_ << "strict graph {" << std::endl;
    }

    ~Printer() {
        file_ << "}" << std::endl;
        file_.close();
    }

    virtual void Visit(BracedStatement* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "BracedStatement");

        for (auto* statement : node->statementRepeated_) {
            ++nodeNumber_;
            PrintEdge(headNodeNumber);
            statement->Accept(node);
        }
    }

    virtual void Visit(ClassDeclaration* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "ClassDeclaration");

        ++nodeNumber;
        PrintEdge(headNodeNumber);
        node->className_->Accept(this);

        ++nodeNumber;
        PrintEdge(headNodeNumber);
        node->baseClass_->Accept(this);

        ++nodeNumber;
        PrintEdge(headNodeNumber);
        node->varDeclarationRepeated_->Accept(this);

        ++nodeNumber;
        PrintEdge(headNodeNumber);
        node->methodDeclarationRepeated_->Accept(this);
    }

    virtual void Visit(ClassDeclarationRepeated* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "ClassDeclarationRepeated");
        for (auto* classDeclaration : node->classDeclarationRepeated_) {
            ++nodeNumber_;
            PrintEdge(headNodeNumber);
            classDeclaration->Accept(this);
        }
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
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "Goal");
        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->mainClass_->Accept(this);
        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->classDeclarationRepeated_->Accept(this);
    }

    virtual void Visit(Identifier* node) override {
    }

    virtual void Visit(MainClass* node) override {
        auto headNodeNumber = nodeNumber_;
        file_ << headNodeNumber << " [label=\"MainClass\"];" << std::endl;
        ++nodeNumber_;
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
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->Accept(this);
    }

    virtual void Visit(TypeIntArray* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->Accept(this);
    }

    virtual void Visit(TypeInt* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->Accept(this);
    }

    virtual void Visit(VarDeclaration* node) override {
        auto headNodeNumber = nodeNumber_;
        file_ << headNodeNumber << " [label=\"VarDeclaration\"];" << std::endl;

        ++nodeNumber_;
        file_ << headNodeNumber << " -- " << nodeNumber_ << std::endl;
        node->type_->Accept(this);

        ++nodeNumber_;
        file_ << headNodeNumber << " -- " << nodeNumber_ << std::endl;
        node->varName_->Accept(this);
    }

    virtual void Visit(VarDeclarationRepeated* node) override {
        auto headNodeNumber = nodeNumber_;
        file_ << headNodeNumber << " [label=\"VarDeclarationRepeated\"];" << std::endl;

        for (auto* VarDeclaration : node->varDeclarationRepeated_) {
            ++nodeNumber_;
            file_ << headNodeNumber << " -- " << nodeNumber_ << std::endl;
            VarDeclaration->Accept(this);
        }
    }

private:
    void PrintHead(int headNodeNumber, const std::string& label) {
        std::cout << headNodeNumber << " [label=\"" << label << "\"];" << std::endl;
    }

    void PrintEdge(int headNodeNumber) {
        std::cout << headNodeNumber << " -- " << nodeNumber_ << std::endl;
    }

private:
    std::ofstream file_;
    int nodeNumber_;
};
