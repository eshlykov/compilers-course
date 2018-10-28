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
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "StatementAssignmentArray");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->identifier_->Accept(this);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->expressionFirst_->Accept(this);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->expressionSecond_->Accept(this);
    }

    virtual void Visit(StatementAssignment* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "StatementAssignment");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->identifier_->Accept(this);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->expression_->Accept(this);
    }

    virtual void Visit(Statement* node) override {
    }

    virtual void Visit(StatementIfElse* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "StatementIfElse");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->condition_->Accept(this);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->trueStatement_->Accept(this);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->falseStatement_->Accept(this);
    }

    virtual void Visit(StatementPrint* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "StatementPrint");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->expression_->Accept(this);
    }

    virtual void Visit(StatementRepeated* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "StatementRepeated");

        for (auto* statement : node->statementRepeated_) {
            ++nodeNumber_;
            PrintEdge(headNodeNumber);
            statement->Accept(this)
        }
    }

    virtual void Visit(StatementWhile* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "StatementWhile");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->condition_->Accept(this);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->trueStatement_->Accept(this);
    }

    virtual void Visit(TypeBoolean* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "TypeIdentifierCommaTypeIdentifierRepeatedOptional");
    }

    virtual void Visit(Type* node) override {

    }

    virtual void Visit(TypeIdentifierCommaTypeIdentifierRepeated* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "TypeIdentifierCommaTypeIdentifierRepeatedOptional");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->type_->Accept(this);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->identifier_->Accept(this);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->commaTypeIdenfifierRepeated_->Accept(this);
    }

    virtual void Visit(TypeIdentifierCommaTypeIdentifierRepeatedOptional* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "TypeIdentifierCommaTypeIdentifierRepeatedOptional");

        if (node->typeIdentifierCommaTypeIdentifierRepeated_.has_value()) {
            ++nodeNumber_;
            PrintEdge(headNodeNumber);
            node->typeIdentifierCommaTypeIdentifierRepeated_->Accept(this);
        }
    }

    virtual void Visit(TypeIdentifier* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "TypeIdentifier");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->className_->Accept(this);
    }

    virtual void Visit(TypeIntArray* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "TypeIntArray");
    }

    virtual void Visit(TypeInt* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "TypeInt");
    }

    virtual void Visit(VarDeclaration* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "VarDeclaration");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->type_->Accept(this);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->varName_->Accept(this);
    }

    virtual void Visit(VarDeclarationRepeated* node) override {
        auto headNodeNumber = nodeNumber_;
        PrintHead("VarDeclarationRepeated");

        for (auto* varDeclaration : node->varDeclarationRepeated_) {
            ++nodeNumber_;
            PrintEdge(headNodeNumber);
            varDeclaration->Accept(this);
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
