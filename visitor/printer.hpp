#pragma once

#include "../ast.hpp"
#include "visitor.hpp"
#include <fstream>
#include <string>

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

    virtual void Visit(ConditionStatement* node) override final {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "LoopStatement");

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

    virtual void Visit(IntArrayConstructorExpression* node) override final {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "IntArrayConstructorExpression");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->expression_->Accept(this);
    }

    virtual void Visit(LengthExpression* node) override final {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "LengthExpression");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->expression_->Accept(this);
    }

    virtual void Visit(LoopStatement* node) override final {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "LoopStatement");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->condition_->Accept(this);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->statement_->Accept(this);
    }

    virtual void Visit(MainClass* node) override final {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "MainClass : " + node->className_);

        ++nodeNumber_;
        PrintLeaf(headNodeNumber, "Argv", node->argv_);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->mainBody_->Accept(this);
    }

    virtual void Visit(MethodBody* node) override final {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "MethodBody");

        for (auto* argument : node->variables_) {
            ++nodeNumber_;
            PrintEdge(headNodeNumber);
            argument->Accept(this);
        }

        for (auto* argument : node->statements_) {
            ++nodeNumber_;
            PrintEdge(headNodeNumber);
            argument->Accept(this);
        }

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->returnExpression_->Accept(this);
    }

    virtual void Visit(MethodCallExpression* node) override final {
        auto headNodeNumber = nodeNumber_;
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
        auto headNodeNumber = nodeNumber_;
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
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "! Expression");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->expression_->Accept(this);
    }

    virtual void Visit(NumberExpression* node) override final {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, std::to_string(node->value_));
    }

    virtual void Visit(ParensExpression* node) override final {
        auto headNodeNumber = nodeNumber_;
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
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "StatementPrint");

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->expression_->Accept(this);
    }

    virtual void Visit(Program* node) override final {
        auto headNodeNumber = nodeNumber_;
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
        auto headNodeNumber = nodeNumber_;
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
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "UserTypeConstructorExpression : " + node->name_);
    }

    virtual void Visit(UserType* node) override final {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "UserType : " + node->className_);
    }

    virtual void Visit(VarDeclaration* node) override final {
        auto headNodeNumber = nodeNumber_;
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
