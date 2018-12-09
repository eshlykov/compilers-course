#include "ir-printer.hpp"

IrPrinter::IrPrinter(const std::string& filename) :
        file_{filename},
        nodeNumber_{0} {
    file_ << "strict graph {" << std::endl;
}

IrPrinter::~IrPrinter() {
    file_ << "}" << std::endl;
    file_.close();
}

void IrPrinter::Visit(IrBinaryOperator* node) {
    int headNodeNumber = nodeNumber_;

    switch (node->arithmeticOperator_) {
        case IrArithmeticOperator::Plus:
            PrintHead(headNodeNumber, "ArithmeticOperator : +");
            break;
        case IrArithmeticOperator::Minus:
            PrintHead(headNodeNumber, "ArithmeticOperator : -");
            break;
        case IrArithmeticOperator::Multiplication:
            PrintHead(headNodeNumber, "ArithmeticOperator : *");
            break;
        default:
            break;
    }

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->left_->Accept(this);

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->right_->Accept(this);
}

void IrPrinter::Visit(IrCall* node) {
    int headNodeNumber = nodeNumber_;
    PrintHead(headNodeNumber, "Call");

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->expression_->Accept(this);

    for (auto& expression : node->expressionList_) {
        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        expression->Accept(this);
    }
}

void IrPrinter::Visit(IrConditionalJump* node) {
    int headNodeNumber = nodeNumber_;

    switch (node->logicalOperator_) {
        case IrLogicalOperator::And:
            PrintHead(headNodeNumber, "LogicalOperator : &&");
            break;
        case IrLogicalOperator::Less:
            PrintHead(headNodeNumber, "LogicalOperator : <");
            break;
    }

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->expressionLeft_->Accept(this);

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->expressionRight_->Accept(this);

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->labelIf_->Accept(this);

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->labelElse_->Accept(this);
}

void IrPrinter::Visit(IrConstant* node) {
    PrintHead(nodeNumber_, "Value : " + std::to_string(node->value_));
}

void IrPrinter::Visit(IrJump* node) {
    int headNodeNumber = nodeNumber_;
    PrintHead(headNodeNumber, "Jump");

    for (auto& label : node->labels_) {
        ++nodeNumber_;
        PrintEdge(headNodeNumber);
        label->Accept(this);
    }
}

void IrPrinter::Visit(IrLabel* node) {
    PrintHead(nodeNumber_, "Label : " + node->label_);
}

void IrPrinter::Visit(IrMemory* node) {
    int headNodeNumber = nodeNumber_;
    PrintHead(headNodeNumber, "Memory");

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->expression_->Accept(this);
}

void IrPrinter::Visit(IrMove* node) {
    int headNodeNumber = nodeNumber_;
    PrintHead(headNodeNumber, "Move");

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->destination_->Accept(this);

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->source_->Accept(this);
}

void IrPrinter::Visit(IrName* node) {
    int headNodeNumber = nodeNumber_;
    PrintHead(headNodeNumber, "Name");

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->label_->Accept(this);
}

void IrPrinter::Visit(IrSequence* node) {
    int headNodeNumber = nodeNumber_;
    PrintHead(headNodeNumber, "Sequence");

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->leftStatement_->Accept(this);

    ++nodeNumber_;
    PrintEdge(headNodeNumber);
    node->rightStatement_->Accept(this);
}

void IrPrinter::Visit(IrTemporary* node) {
    PrintHead(nodeNumber_, "Temporary : " + node->temporary_);
}

void IrPrinter::PrintHead(int headNodeNumber, const std::string& label) {
    file_ << headNodeNumber << " [label=\"" << label << "\"];" << std::endl;
}

void IrPrinter::PrintEdge(int headNodeNumber) {
    file_ << headNodeNumber << " -- " << nodeNumber_ << std::endl;
}

void IrPrinter::PrintLeaf(int headNodeNumber, const std::string& label, const std::string& name) {
    file_ << nodeNumber_ << " [label=\"" << label << " : " << name << "\"];" << std::endl;
    file_ << headNodeNumber << " -- " << nodeNumber_ << std::endl;
}
