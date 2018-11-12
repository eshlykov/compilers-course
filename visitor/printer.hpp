#pragma once

#include "../ast.hpp"
#include "visitor.hpp"
#include <fstream>
#include <optional>
#include <string>
#include <vector>

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

      virtual void Visit(AssignmentByIndexStatement* node) override final {
        int headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "AssignmentByIndexStatement");

        ++nodeNumber_;
        PrintLeaf(headNodeNumber, "Array", node->array_);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->index_->Accept(this);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->expression_->Accept(this);
    }

    virtual void Visit(AssignmentStatement* node) override final {
        int headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "AssignmentStatement");

        ++nodeNumber_;
        PrintLeaf(headNodeNumber, "Variable", node->variable_);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->expression_->Accept(this);
    }

    virtual void Visit(BinaryOperatorExpression* node) override final {
        int headNodeNumber = nodeNumber_;

        switch (node->binaryOperator_) {
        case BinaryOperator::BO_And:
            PrintHead(headNodeNumber, "BinaryOperator : &&");
            break;
        case BinaryOperator::BO_Less:
            PrintHead(headNodeNumber, "BinaryOperator : <");
            break;
        case BinaryOperator::BO_Plus:
            PrintHead(headNodeNumber, "BinaryOperator : +");
            break;
        case BinaryOperator::BO_Minus:
            PrintHead(headNodeNumber, "BinaryOperator : -");
            break;
        case BinaryOperator::BO_Star:
            PrintHead(headNodeNumber, "BinaryOperator : *");
            break;
        default:
            break;
        }

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->lhs_->Accept(this);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->rhs_->Accept(this);
    }

    virtual void Visit(BooleanExpression* node) override final {
        PrintHead(nodeNumber_, "Boolean : " + std::string{node->value_ ? "true" : "false"});
    }

    virtual void Visit(ClassBody* node) override final {
        int headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "ClassBody");

        for (auto* variable : node->variables_) {
            ++nodeNumber_;
            PrintEdge(headNodeNumber);
            variable->Accept(this);
        }

        for (auto* method : node->methods_) {
            ++nodeNumber_;
            PrintEdge(headNodeNumber);
            method->Accept(this);
        }
    }

    virtual void Visit(ClassDeclaration* node) override final {
        int headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "ClassDeclaration : " + node->className_);

        if (node->extendsForClass_.has_value()) {
            ++nodeNumber_;
            PrintLeaf(headNodeNumber, "Extends", node->extendsForClass_.value());
        }

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->classBody_->Accept(this);
    }

    virtual void Visit(ConditionStatement* node) override final {
        int headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "ConditionStatement");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->condition_->Accept(this);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->ifStatement_->Accept(this);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->elseStatement_->Accept(this);
    }

    virtual void Visit(IdentifierExpression* node) override final {
        PrintHead(nodeNumber_, "Identifier : " + node->name_);
    }

    virtual void Visit(IndexExpression* node) override final {
        int headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "IndexExpression");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->lhs_->Accept(this);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->rhs_->Accept(this);
    }

    virtual void Visit(IntArrayConstructorExpression* node) override final {
        int headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "IntArrayConstructorExpression");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->expression_->Accept(this);
    }

    virtual void Visit(LengthExpression* node) override final {
        int headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "LengthExpression");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->expression_->Accept(this);
    }

    virtual void Visit(LoopStatement* node) override final {
        int headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "LoopStatement");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->condition_->Accept(this);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->statement_->Accept(this);
    }

    virtual void Visit(MainClass* node) override final {
        int headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "MainClass : " + node->className_);

        ++nodeNumber_;
        PrintLeaf(headNodeNumber, "Argv", node->argv_);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->mainBody_->Accept(this);
    }

    virtual void Visit(MethodBody* node) override final {
        int headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "MethodBody");

        for (auto* variable : node->variables_) {
            ++nodeNumber_;
            PrintEdge(headNodeNumber);
            variable->Accept(this);
        }

        for (auto* statement : node->statements_) {
            ++nodeNumber_;
            PrintEdge(headNodeNumber);
            statement->Accept(this);
        }

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->returnExpression_->Accept(this);
    }

    virtual void Visit(MethodCallExpression* node) override final {
        int headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "MethodCallExpression");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->expression_->Accept(this);

        ++nodeNumber_;
        PrintLeaf(headNodeNumber, "Name", node->methodName_);

        for (auto* argument : node->argumentsList_) {
            ++nodeNumber_;
            PrintEdge(headNodeNumber);
            argument->Accept(this);
        }
    }

    virtual void Visit(MethodDeclaration* node) override final {
        int headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "MethodDeclaration : " + node->methodName_);

        for (auto* argument : node->argumentsList_) {
            ++nodeNumber_;
            PrintEdge(headNodeNumber);
            argument->Accept(this);
        }

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->methodBody_->Accept(this);
    }

    virtual void Visit(NotExpression* node) override final {
        int headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "! Expression");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->expression_->Accept(this);
    }

    virtual void Visit(NumberExpression* node) override final {
        int headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "Number : " + std::to_string(node->value_));
    }

    virtual void Visit(ParensExpression* node) override final {
        int headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "( Expression )");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->expression_->Accept(this);
    }

    virtual void Visit(PrimitiveType* node) override final {
        switch (node->typeKind_) {
        case TypeKind::TK_IntArray:
            PrintHead(nodeNumber_, "PrimitiveType : int[]");
            break;
        case TypeKind::TK_Boolean:
            PrintHead(nodeNumber_, "PrimitiveType : boolean");
            break;
        case TypeKind::TK_Int:
            PrintHead(nodeNumber_, "PrimitiveType : int");
            break;
        default:
            break;
        }
    }

    virtual void Visit(PrintStatement* node) override final {
        int headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "StatementPrint");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->expression_->Accept(this);
    }

    virtual void Visit(Program* node) override final {
        int headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "Program");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->mainClass_->Accept(this);

        for (auto* classDeclaration : node->classDeclarations_) {
            ++nodeNumber_;
            PrintEdge(headNodeNumber);
            classDeclaration->Accept(this);
        }
    }

    virtual void Visit(ScopeStatement* node) override final {
        int headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "{ Statement }");

        for (auto* statement : node->statements_) {
            ++nodeNumber_;
            PrintEdge(headNodeNumber);
            statement->Accept(this);
        }
    }

    virtual void Visit(ThisExpression* node) override final {
        PrintHead(nodeNumber_, "This");
    }

    virtual void Visit(UserTypeConstructorExpression* node) override final {
        int headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "UserTypeConstructorExpression : " + node->name_);
    }

    virtual void Visit(UserType* node) override final {
        int headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "UserType : " + node->className_);
    }

    virtual void Visit(VarDeclaration* node) override final {
        int headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "Variable");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->type_->Accept(this);

        ++nodeNumber_;
        PrintLeaf(headNodeNumber, "Name", node->name_);
    }

private:
    void PrintHead(int headNodeNumber, const std::string& label) {
        file_ << headNodeNumber << " [label=\"" << label << "\"];" << std::endl;
    }

    void PrintEdge(int headNodeNumber) {
        file_ << headNodeNumber << " -- " << nodeNumber_ << std::endl;
    }

    void PrintLeaf(int headNodeNumber, const std::string& label, const std::string& name) {
        file_ << nodeNumber_ << " [label=\"" << label << " : " << name << "\"];" << std::endl;
        file_ << headNodeNumber << " -- " << nodeNumber_ << std::endl;
    }

private:
    std::ofstream file_;
    int nodeNumber_;
};
