#pragma once

#include "../ast.hpp"
#include "visitor.hpp"
#include <fstream>
#include <string>

class Printer : public Visitor {
public:
    Printer(const std::string& filename) :
        file_{filename},
        nodeNumber_{0} {
        file_ << "strict graph {" << std::endl;
    }

    ~Printer() {
        file_ << "}" << std::endl;
        file_.close();
    }

    virtual void Visit(AssignmentByIndexStatement* node) override final {
        auto headNodeNumber = nodeNumber_;
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
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, ":=");

        ++nodeNumber_;
        PrintLeaf(headNodeNumber, "Variable", node->variable_);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->expression_->Accept(this);
    }

    virtual void Visit(BinaryOperatorExpression* node) override final {
        auto headNodeNumber = nodeNumber_;

        switch (node->binaryOperator_) {
        case BO_And:
            PrintHead(headNodeNumber, "&&");
            break;
        case BO_Less:
            PrintHead(headNodeNumber, "<");
            break;
        case BO_Plus:
            PrintHead(headNodeNumber, "+");
            break;
        case BO_Minus:
            PrintHead(headNodeNumber, "-");
            break;
        case BO_Star:
            PrintHead(headNodeNumber, "*");
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
        PrintHead(nodeNumber_, "Boolean : " + node->value_);
    }

    virtual void Visit(ClassBody* node) override final {
        auto headNodeNumber = nodeNumber_;
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
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "ClassDeclaration : " + node->className);

        if (node->extendsForClass_.has_value()) {
            ++nodeNumber_;
            PrintLeaf(headNodeNumber, "Extends", node->extendsForClass_.value());
        }

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->classBody_->Accept(this);
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

    virtual void Visit(MainClass* node) override final {
        auto headNodeNumber = nodeNumber_;
        PrintHead(headNodeNumber, "MainClass : " + node->className_);

        ++nodeNumber_;
        PrintLeaf(headNodeNumber, "Argv", node->argv_);

        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        node->mainBody_->Accept(this);
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
