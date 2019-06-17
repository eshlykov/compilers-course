#include <cassert>
#include <cg/node/commands.hpp>
#include <cg/visitor/assembly-command.hpp>
#include <cg/visitor/command-emitter-visitor.hpp>
#include <string>

using namespace Cg;
using LOT = Irt::LogicOperatorTypes;

int AssemblyCommand::registerCounter_ = 0;

CommandEmitterVisitor::CommandEmitterVisitor() : Visitor(false) {
  tempToRegister_["$fp"] = "rbp";
  tempToRegister_["$rv"] = "rax";
}

void CommandEmitterVisitor::Visit(const ExpStatementCommand* statement) {
  statement->GetExpression()->Accept(this);
}

void CommandEmitterVisitor::Visit(const ConditionalJumpCommand* command) {
  const Expression* left = command->LeftPart();
  const Expression* right = command->RightPart();

  left->Accept(this);
  std::string leftRegister = lastRegisterValue_;
  right->Accept(this);
  std::string rightRegister = lastRegisterValue_;

  auto cmp = command->Cmp();
  std::string ret;
  if (cmp == LOT::Equal) {
    ret = "je";
  } else if (cmp == LOT::NotEqual) {
    ret = "jne";
  } else if (cmp == LOT::Less) {
    ret = "jl";
  } else if (cmp == LOT::Greater) {
    ret = "jg";
  } else if (cmp == LOT::LessEqual) {
    ret = "jle";
  } else if (cmp == LOT::GreaterEqual) {
    ret = "jge";
  } else {
    assert(false);
  }

  code_.push_back(AssemblyCommand(ret + " " + command->PositiveLabelName(),
                                  {leftRegister, rightRegister}));
}

void CommandEmitterVisitor::Visit(const JumpCommand* command) {
  code_.push_back(AssemblyCommand("jmp " + command->LabelName(), {}));
}

void CommandEmitterVisitor::Visit(const CallFunctionCommand* command) {
  const std::vector<const Expression*>& arguments = command->Arguments();

  for (auto it = arguments.rbegin(); it != arguments.rend(); ++it) {
    (*it)->Accept(this);
    code_.push_back(AssemblyCommand("push " + lastRegisterValue_, {lastRegisterValue_}));
  }

  code_.push_back(AssemblyCommand("call " + command->Function(), {}));
}

void CommandEmitterVisitor::Visit(const LabelDeclarationCommand* command) {
  code_.push_back(AssemblyCommand(command->Name() + ":", {}));
}

void CommandEmitterVisitor::Visit(const MoveRegisterCommand* command) {
  const Expression* source = command->Source();
  const Expression* destination = command->Destination();

  source->Accept(this);
  std::string sourceRegister = lastRegisterValue_;
  destination->Accept(this);
  std::string destinationRegister = lastRegisterValue_;

  code_.push_back(
      AssemblyCommand("mov " + destinationRegister + ", " + sourceRegister,
                      {sourceRegister, destinationRegister}));
}

void CommandEmitterVisitor::Visit(const TempExpression* expression) {
  std::string tempValue = expression->Name();

  auto pos = tempToRegister_.find(tempValue);
  if (pos == tempToRegister_.end()) {
    code_.push_back(AssemblyCommand(tempValue, {}));
    tempToRegister_[tempValue] = AssemblyCommand::NewRegister(code_);
  }

  lastRegisterValue_ = tempToRegister_[tempValue];
}

void CommandEmitterVisitor::Visit(const AddCommand* expression) {
  const Expression* leftOperand = expression->LeftOperand();
  const Expression* rightOperand = expression->RightOperand();

  leftOperand->Accept(this);
  std::string leftRegister = lastRegisterValue_;
  rightOperand->Accept(this);
  std::string rightRegister = lastRegisterValue_;

  std::string resultRegister = AssemblyCommand::NewRegister(code_);

  code_.push_back(AssemblyCommand("mov " + resultRegister + ", " + leftRegister,
                                  {leftRegister, resultRegister}));
  code_.push_back(
      AssemblyCommand("add " + resultRegister + ", " + rightRegister,
                      {resultRegister, rightRegister}));

  lastRegisterValue_ = resultRegister;
}

void CommandEmitterVisitor::Visit(const AddConstCommand* passedExpression) {
  const Expression* expression = passedExpression->GetExpression();
  const int constant = passedExpression->Constant();

  expression->Accept(this);
  std::string expressionRegister = lastRegisterValue_;

  std::string resultRegister = AssemblyCommand::NewRegister(code_);

  code_.push_back(
      AssemblyCommand("mov " + resultRegister + ", " + expressionRegister,
                      {expressionRegister, resultRegister}));
  code_.push_back(AssemblyCommand(
      "add " + resultRegister + ", $" + std::to_string(constant),
      {resultRegister}));

  lastRegisterValue_ = resultRegister;
}

void CommandEmitterVisitor::Visit(const SubCommand* expression) {
  const Expression* leftOperand = expression->LeftOperand();
  const Expression* rightOperand = expression->RightOperand();

  leftOperand->Accept(this);
  std::string leftRegister = lastRegisterValue_;
  rightOperand->Accept(this);
  std::string rightRegister = lastRegisterValue_;

  std::string resultRegister = AssemblyCommand::NewRegister(code_);

  code_.push_back(AssemblyCommand("mov " + resultRegister + ", " + leftRegister,
                                  {leftRegister, resultRegister}));
  code_.push_back(
      AssemblyCommand("sub " + resultRegister + ", " + rightRegister,
                      {resultRegister, rightRegister}));

  lastRegisterValue_ = resultRegister;
}

void CommandEmitterVisitor::Visit(const SubConstCommand* passedExpression) {
  const Expression* expression = passedExpression->GetExpression();
  const int constant = passedExpression->Constant();

  expression->Accept(this);
  std::string expressionRegister = lastRegisterValue_;

  std::string resultRegister = AssemblyCommand::NewRegister(code_);

  code_.push_back(
      AssemblyCommand("mov " + resultRegister + ", " + expressionRegister,
                      {expressionRegister, resultRegister}));
  code_.push_back(AssemblyCommand(
      "sub " + resultRegister + ", $" + std::to_string(constant),
      {resultRegister}));

  lastRegisterValue_ = resultRegister;
}

void CommandEmitterVisitor::Visit(const MultCommand* expression) {
  const Expression* leftOperand = expression->LeftOperand();
  const Expression* rightOperand = expression->RightOperand();

  leftOperand->Accept(this);
  std::string leftRegister = lastRegisterValue_;
  rightOperand->Accept(this);
  std::string rightRegister = lastRegisterValue_;

  std::string resultRegister = AssemblyCommand::NewRegister(code_);

  // http://www.felixcloutier.com/x86/MUL.html
  code_.push_back(AssemblyCommand("mov rax, " + leftRegister, {leftRegister}));
  code_.push_back(AssemblyCommand("mul " + rightRegister, {rightRegister}));
  code_.push_back(
      AssemblyCommand("mov " + resultRegister + ", rax", {resultRegister}));

  lastRegisterValue_ = resultRegister;
}

void CommandEmitterVisitor::Visit(const DivCommand* expression) {
  const Expression* leftOperand = expression->LeftOperand();
  const Expression* rightOperand = expression->RightOperand();

  leftOperand->Accept(this);
  std::string leftRegister = lastRegisterValue_;
  rightOperand->Accept(this);
  std::string rightRegister = lastRegisterValue_;

  std::string resultRegister = AssemblyCommand::NewRegister(code_);

  // http://www.felixcloutier.com/x86/DIV.html
  code_.push_back(AssemblyCommand("mov rax, " + leftRegister, {leftRegister}));
  code_.push_back(AssemblyCommand("div " + rightRegister, {rightRegister}));
  code_.push_back(
      AssemblyCommand("mov " + resultRegister + ", rax", {resultRegister}));

  lastRegisterValue_ = resultRegister;
}

void CommandEmitterVisitor::Visit(const NullExpression* expression) {
  std::string reg = AssemblyCommand::NewRegister(code_);

  code_.push_back(AssemblyCommand("mov " + reg + ", $0", {reg}));

  lastRegisterValue_ = reg;
}

void CommandEmitterVisitor::Visit(const LoadCommand* expression) {
  const int offset = expression->Offset();
  const Expression* expr = expression->Source();

  expr->Accept(this);
  std::string lastRegister = lastRegisterValue_;

  std::string addressRegister = AssemblyCommand::NewRegister(code_);
  code_.push_back(
      AssemblyCommand("mov " + addressRegister + ", " + lastRegister,
                      {addressRegister, lastRegister}));
  code_.push_back(
      AssemblyCommand("add " + addressRegister + ", $" + std::to_string(offset),
                      {addressRegister}));

  std::string targetRegister = lastRegisterValue_;

  code_.push_back(AssemblyCommand(
      "mov " + targetRegister + ", " + "%(" + addressRegister + ")",
      {targetRegister, addressRegister}));
  lastRegisterValue_ = targetRegister;
}

void CommandEmitterVisitor::Visit(const StoreCommand* expression) {
  const int offset = expression->Offset();
  const Expression* source = expression->Source();
  const Expression* destination = expression->Destination();

  destination->Accept(this);
  std::string destinationRegister = lastRegisterValue_;
  source->Accept(this);
  std::string sourceRegister = lastRegisterValue_;

  std::string addressRegister = AssemblyCommand::NewRegister(code_);
  code_.push_back(
      AssemblyCommand("mov " + addressRegister + ", " + destinationRegister,
                      {addressRegister, destinationRegister}));
  code_.push_back(
      AssemblyCommand("add " + addressRegister + ", $" + std::to_string(offset),
                      {addressRegister}));

  code_.push_back(
      AssemblyCommand("mov %(" + destinationRegister + "), " + sourceRegister,
                      {destinationRegister, sourceRegister}));
}
