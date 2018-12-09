#include "printer.hpp"

Printer::Printer(const std::string& filename) :
        file_{filename},
        nodeNumber_{0} {
    file_ << "strict graph {" << std::endl;
}

Printer::~Printer() {
    file_ << "}" << std::endl;
    file_.close();
}

void Printer::Visit(AssignmentByIndexStatement* node) {
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

void Printer::Visit(AssignmentStatement* node) {
    int headNodeNumber = nodeNumber_;
    PrintHead(headNodeNumber, "AssignmentStatement");

    ++nodeNumber_;
    PrintLeaf(headNodeNumber, "Variable", node->variable_);

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->expression_->Accept(this);
}

void Printer::Visit(BinaryOperatorExpression* node) {
    int headNodeNumber = nodeNumber_;

    switch (node->binaryOperator_) {
        case BinaryOperator::And:
            PrintHead(headNodeNumber, "BinaryOperator : &&");
            break;
        case BinaryOperator::Less:
            PrintHead(headNodeNumber, "BinaryOperator : <");
            break;
        case BinaryOperator::Plus:
            PrintHead(headNodeNumber, "BinaryOperator : +");
            break;
        case BinaryOperator::Minus:
            PrintHead(headNodeNumber, "BinaryOperator : -");
            break;
        case BinaryOperator::Star:
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

void Printer::Visit(BooleanExpression* node) {
    PrintHead(nodeNumber_, "Boolean : " + std::string{node->value_ ? "true" : "false"});
}

void Printer::Visit(ClassBody* node) {
    int headNodeNumber = nodeNumber_;
    PrintHead(headNodeNumber, "ClassBody");

    for (auto& variable : node->variables_) {
        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        variable->Accept(this);
    }

    for (auto& method : node->methods_) {
        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        method->Accept(this);
    }
}

void Printer::Visit(ClassDeclaration* node) {
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

void Printer::Visit(ConditionStatement* node) {
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

void Printer::Visit(IdentifierExpression* node) {
    PrintHead(nodeNumber_, "Identifier : " + node->name_);
}

void Printer::Visit(IndexExpression* node) {
    int headNodeNumber = nodeNumber_;
    PrintHead(headNodeNumber, "IndexExpression");

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->lhs_->Accept(this);

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->rhs_->Accept(this);
}

void Printer::Visit(IntArrayConstructorExpression* node) {
    int headNodeNumber = nodeNumber_;
    PrintHead(headNodeNumber, "IntArrayConstructorExpression");

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->expression_->Accept(this);
}

void Printer::Visit(LengthExpression* node) {
    int headNodeNumber = nodeNumber_;
    PrintHead(headNodeNumber, "LengthExpression");

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->expression_->Accept(this);
}

void Printer::Visit(LoopStatement* node) {
    int headNodeNumber = nodeNumber_;
    PrintHead(headNodeNumber, "LoopStatement");

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->condition_->Accept(this);

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->statement_->Accept(this);
}

void Printer::Visit(MainClass* node) {
    int headNodeNumber = nodeNumber_;
    PrintHead(headNodeNumber, "MainClass : " + node->className_);

    ++nodeNumber_;
    PrintLeaf(headNodeNumber, "Argv", node->argv_);

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->mainBody_->Accept(this);
}

void Printer::Visit(MethodBody* node) {
    int headNodeNumber = nodeNumber_;
    PrintHead(headNodeNumber, "MethodBody");

    for (auto& variable : node->variables_) {
        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        variable->Accept(this);
    }

    for (auto& statement : node->statements_) {
        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        statement->Accept(this);
    }

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->returnExpression_->Accept(this);
}

void Printer::Visit(MethodCallExpression* node) {
    int headNodeNumber = nodeNumber_;
    PrintHead(headNodeNumber, "MethodCallExpression");

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->expression_->Accept(this);

    ++nodeNumber_;
    PrintLeaf(headNodeNumber, "Name", node->methodName_);

    for (auto& argument : node->argumentsList_) {
        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        argument->Accept(this);
    }
}

void Printer::Visit(MethodDeclaration* node) {
    int headNodeNumber = nodeNumber_;
    PrintHead(headNodeNumber, "MethodDeclaration : " + node->methodName_);

    for (auto& argument : node->argumentsList_) {
        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        argument->Accept(this);
    }

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->methodBody_->Accept(this);
}

void Printer::Visit(NotExpression* node) {
    int headNodeNumber = nodeNumber_;
    PrintHead(headNodeNumber, "! Expression");

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->expression_->Accept(this);
}

void Printer::Visit(NumberExpression* node) {
    int headNodeNumber = nodeNumber_;
    PrintHead(headNodeNumber, "Number : " + std::to_string(node->value_));
}

void Printer::Visit(PrintStatement* node) {
    int headNodeNumber = nodeNumber_;
    PrintHead(headNodeNumber, "StatementPrint");

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->expression_->Accept(this);
}

void Printer::Visit(Program* node) {
    int headNodeNumber = nodeNumber_;
    PrintHead(headNodeNumber, "Program");

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->mainClass_->Accept(this);

    for (auto& classDeclaration : node->classDeclarations_) {
        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        classDeclaration->Accept(this);
    }
}

void Printer::Visit(ScopeStatement* node) {
    int headNodeNumber = nodeNumber_;
    PrintHead(headNodeNumber, "{ Statement }");

    for (auto& statement : node->statements_) {
        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        statement->Accept(this);
    }
}

void Printer::Visit(ThisExpression* node) {
    PrintHead(nodeNumber_, "This");
}

void Printer::Visit(Type* node) {
    try {
        switch (std::get<TypeKind>(node->type_)) {
        case TypeKind::IntArray:
            PrintHead(nodeNumber_, "Type : int[]");
            break;
        case TypeKind::Boolean:
            PrintHead(nodeNumber_, "Type : boolean");
            break;
        case TypeKind::Int:
            PrintHead(nodeNumber_, "Type : int");
            break;
        default:
            break;
        }
    } catch (const std::bad_variant_access&) {
        PrintHead(nodeNumber_, "Type : " + std::get<std::string>(node->type_));
    }
}

void Printer::Visit(UserTypeConstructorExpression* node) {
    int headNodeNumber = nodeNumber_;
    PrintHead(headNodeNumber, "UserTypeConstructorExpression : " + node->name_);
}

void Printer::Visit(VarDeclaration* node) {
    int headNodeNumber = nodeNumber_;
    PrintHead(headNodeNumber, "Variable");

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->type_->Accept(this);

    ++nodeNumber_;
    PrintLeaf(headNodeNumber, "Name", node->name_);
}

void Printer::PrintHead(int headNodeNumber, const std::string& label) {
    file_ << headNodeNumber << " [label=\"" << label << "\"];" << std::endl;
}

void Printer::PrintEdge(int headNodeNumber) {
    file_ << headNodeNumber << " -- " << nodeNumber_ << std::endl;
}

void Printer::PrintLeaf(int headNodeNumber, const std::string& label, const std::string& name) {
    file_ << nodeNumber_ << " [label=\"" << label << " : " << name << "\"];" << std::endl;
    file_ << headNodeNumber << " -- " << nodeNumber_ << std::endl;
}
