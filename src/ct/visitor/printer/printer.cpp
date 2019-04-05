#include "printer.hpp"
#include "../../frame/frame.hpp"

namespace Ct {

Printer::Printer(const std::string& filename)
    : file_{filename}, nodeNumber_{0} {
  file_ << "strict graph {" << std::endl;
}

Printer::~Printer() {
  file_ << "}" << std::endl;
  file_.close();
}

void Printer::Visit(BinaryOperator* node) {
  int headNodeNumber = nodeNumber_;
  PrintHead(headNodeNumber, "BinaryOperator");

  ++nodeNumber_;
  switch (node->arithmeticOperator_) {
    case ArithmeticOperator::Plus:
      PrintLeaf(headNodeNumber, "ArithmeticOperator", "+");
      break;
    case ArithmeticOperator::Minus:
      PrintLeaf(headNodeNumber, "ArithmeticOperator", "-");
      break;
    case ArithmeticOperator::Multiplication:
      PrintLeaf(headNodeNumber, "ArithmeticOperator", "*");
      break;
  }

  ++nodeNumber_;
  PrintEdge(headNodeNumber);
  node->leftExpression_->Accept(this);

  ++nodeNumber_;
  PrintEdge(headNodeNumber);
  node->rightExpression_->Accept(this);
}

void Printer::Visit(Call* node) {
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

void Printer::Visit(ConditionalJump* node) {
  int headNodeNumber = nodeNumber_;
  PrintHead(headNodeNumber, "ConditionalJump");

  ++nodeNumber_;
  switch (node->logicalOperator_) {
    case LogicalOperator::And:
      PrintLeaf(headNodeNumber, "LogicalOperator", "&&");
      break;
    case LogicalOperator::Less:
      PrintLeaf(headNodeNumber, "LogicalOperator", "<");
      break;
    case LogicalOperator::Equal:
      PrintLeaf(headNodeNumber, "LogicalOperator", "==");
      break;
  }

  ++nodeNumber_;
  PrintEdge(headNodeNumber);
  node->expressionLeft_->Accept(this);

  ++nodeNumber_;
  PrintEdge(headNodeNumber);
  node->expressionRight_->Accept(this);

  ++nodeNumber_;
  PrintLeaf(headNodeNumber, "AddressIf", node->addressIf_.ToString());

  ++nodeNumber_;
  PrintLeaf(headNodeNumber, "AddressElse", node->addressElse_.ToString());
}

void Printer::Visit(Constant* node) {
  PrintHead(nodeNumber_, "Constant : " + std::to_string(node->value_));
}

void Printer::Visit(ExpressionSequence* node) {
  int headNodeNumber = nodeNumber_;
  PrintHead(headNodeNumber, "ExpressionSequence");

  ++nodeNumber_;
  PrintEdge(headNodeNumber);
  node->statement_->Accept(this);

  ++nodeNumber_;
  PrintEdge(headNodeNumber);
  node->expression_->Accept(this);
}

void Printer::Visit(Jump* node) {
  int headNodeNumber = nodeNumber_;
  PrintHead(headNodeNumber, "Jump");

  ++nodeNumber_;
  PrintLeaf(headNodeNumber, "Address", node->address_.ToString());
}

void Printer::Visit(Label* node) {
  PrintHead(nodeNumber_, "Label : " + node->address_.ToString());
}

void Printer::Visit(Memory* node) {
  int headNodeNumber = nodeNumber_;
  PrintHead(headNodeNumber, "Memory");

  ++nodeNumber_;
  PrintEdge(headNodeNumber);
  node->expression_->Accept(this);
}

void Printer::Visit(Move* node) {
  int headNodeNumber = nodeNumber_;
  PrintHead(headNodeNumber, "Move");

  ++nodeNumber_;
  PrintEdge(headNodeNumber);
  node->destination_->Accept(this);

  ++nodeNumber_;
  PrintEdge(headNodeNumber);
  node->source_->Accept(this);
}

void Printer::Visit(Name* node) {
  int headNodeNumber = nodeNumber_;
  PrintHead(headNodeNumber, "Name");

  ++nodeNumber_;
  PrintLeaf(headNodeNumber, "Address", node->address_.ToString());
}

void Printer::Visit(StatementSequence* node) {
  int headNodeNumber = nodeNumber_;
  PrintHead(headNodeNumber, "StatementSequence");

  ++nodeNumber_;
  PrintEdge(headNodeNumber);
  node->leftStatement_->Accept(this);

  ++nodeNumber_;
  PrintEdge(headNodeNumber);
  node->rightStatement_->Accept(this);
}

void Printer::Visit(Temporary* node) {
  if (node->storage_ == Frame::FramePointer_) {
    PrintHead(nodeNumber_, "FramePointer");
  } else {
    PrintHead(nodeNumber_, "Temporary : " + node->storage_.ToString());
  }
}

void Printer::Visit(Void* node) {
  int headNodeNumber = nodeNumber_;
  PrintHead(headNodeNumber, "Void");

  ++nodeNumber_;
  PrintEdge(headNodeNumber);
  node->expression_->Accept(this);
}

void Printer::Next() { ++nodeNumber_; }

void Printer::PrintHead(int headNodeNumber, const std::string& label) {
  file_ << headNodeNumber << " [label=\"" << label << "\"];" << std::endl;
}

void Printer::PrintEdge(int headNodeNumber) {
  file_ << headNodeNumber << " -- " << nodeNumber_ << std::endl;
}

void Printer::PrintLeaf(int headNodeNumber, const std::string& label,
                        const std::string& name) {
  file_ << nodeNumber_ << " [label=\"" << label << " : " << name << "\"];"
        << std::endl;
  file_ << headNodeNumber << " -- " << nodeNumber_ << std::endl;
}

}  // namespace Ct
