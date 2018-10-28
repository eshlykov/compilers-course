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

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->statementRepeated_->Accept(this);
    }

    virtual void Visit(ClassDeclaration* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "ClassDeclaration");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->className_->Accept(this);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->baseClass_->Accept(this);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->varDeclarationRepeated_->Accept(this);

        ++nodeNumber_;
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
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "ExpressionAtExpression");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->lhs_->Accept(this);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->rhs_->Accept(this);
    }

    virtual void Visit(ExpressionBang* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "ExpressionBang");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->expression_->Accept(this);
    }

    virtual void Visit(ExpressionBinaryOperatorExpression* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "ExpressionBinaryOperatorExpression");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->lhs_->Accept(this);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->rhs_->Accept(this);
    }

    virtual void Visit(ExpressionCommaExpressionRepeated* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "ExpressionCommaExpressionRepeated");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->expression_->Accept(this);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->commaExpressionRepeated_->Accept(this);
    }

    virtual void Visit(ExpressionCommaExpressionRepeatedOptional* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "ExpressionCommaExpressionRepeatedOptional");

        if (node->expressionCommaExpressionRepeated_.has_value()) {
            ++nodeNumber_;
            PrintEdge(headNodeNumber);
            node->expressionCommaExpressionRepeated_.value()->Accept(this);
        }
    }

    virtual void Visit(ExpressionFalse* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "ExpressionFalse");
    }

    virtual void Visit(Expression* node) override {
    }

    virtual void Visit(ExpressionIdentifierExpressionCommaExpressionRepeatedOptional* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "ExpressionIdentifierExpressionCommaExpressionRepeatedOptional");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->expression_->Accept(this);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->identifier_->Accept(this);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->expressionCommaExpressionRepeatedOptional_->Accept(this);
    }

    virtual void Visit(ExpressionLength* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "ExpressionLength");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->expression_->Accept(this);
    }

    virtual void Visit(ExpressionNewExpression* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "ExpressionNewExpression");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->expression_->Accept(this);
    }

    virtual void Visit(ExpressionNewIdentifier* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "ExpressionNewIdentifier");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->identifier_->Accept(this);
    }

    virtual void Visit(ExpressionNumber* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "ExpressionNumber");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->number_->Accept(this);
    }

    virtual void Visit(ExpressionParentheses* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "ExpressionParentheses");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->expression_->Accept(this);
    }

    virtual void Visit(ExpressionThis* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "ExpressionParentheses");
    }

    virtual void Visit(ExpressionTrue* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "ExpressionParentheses");
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
        PrintHead(headNodeNumber, "TypeIdentifier");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->Accept(this);
    }

    virtual void Visit(TypeIntArray* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "TypeIntArray");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->Accept(this);
    }

    virtual void Visit(TypeInt* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "TypeInt");

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
        file_ << headNodeNumber << " [label=\"" << label << "\"];" << std::endl;
    }

    void PrintEdge(int headNodeNumber) {
        file_ << headNodeNumber << " -- " << nodeNumber_ << std::endl;
    }

private:
    std::ofstream file_;
    int nodeNumber_;
};
