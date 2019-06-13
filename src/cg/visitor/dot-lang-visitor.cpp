#include <cg/node/commands.hpp>
#include <cg/node/node-names.hpp>
#include <cg/visitor/dot-lang-visitor.hpp>

using namespace Cg;

void DotLangVisitor::DoAddEdge(const std::string& nodeFromName,
                               const std::string& nodeToName) {
  treeEdges_[nodeFromName].push_back(nodeToName);
}

std::string DotLangVisitor::GetTraversalInDotLanguage() const {
  std::stringstream sstream;
  sstream << "digraph {" << std::endl;
  sstream << '\t' << "ordering = out;" << std::endl;
  for (auto it = treeEdges_.begin(); it != treeEdges_.end(); ++it) {
    const std::string& fromNode = it->first;
    for (const std::string& toNode : it->second) {
      sstream << '\t' << fromNode << " -> " << toNode << ';' << std::endl;
    }
  }
  sstream << '}' << std::endl;

  return sstream.str();
}

// ___

void DotLangVisitor::Visit(const ConditionalJumpCommand* command) {
  std::string nodeName = GenerateNodeName(NodeNames::cjump_);
  visitedNodeStack_.push_back(nodeName);

  command->LeftPart()->Accept(this);
  DoAddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  command->RightPart()->Accept(this);
  DoAddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();
}

void DotLangVisitor::Visit(const JumpCommand* command) {
  std::string nodeName = GenerateNodeName(NodeNames::jump_);
  visitedNodeStack_.push_back(nodeName);

  std::string labelNodeName = "\"" + GenerateNodeName("Label") + ": ";
  labelNodeName += command->LabelName() + "\"";
  DoAddEdge(nodeName, labelNodeName);
}

void DotLangVisitor::Visit(const CallFunctionCommand* command) {
  std::string nodeName = GenerateNodeName(NodeNames::call_);
  visitedNodeStack_.push_back(nodeName);

  std::string functionNodeName = "\"" + GenerateNodeName("Function") + ": ";
  functionNodeName += command->Function() + "\"";
  DoAddEdge(nodeName, functionNodeName);

  for (auto argument : command->Arguments()) {
    argument->Accept(this);
    DoAddEdge(nodeName, visitedNodeStack_.back());
    visitedNodeStack_.pop_back();
  }
}

void DotLangVisitor::Visit(const LabelDeclarationCommand* command) {
  std::string nodeName = GenerateNodeName(NodeNames::label_);
  visitedNodeStack_.push_back(nodeName);

  std::string labelNodeName = "\"" + GenerateNodeName("Label") + ": ";
  labelNodeName += command->Name() + "\"";
  DoAddEdge(nodeName, labelNodeName);
}

void DotLangVisitor::Visit(const MoveRegisterCommand* command) {
  std::string nodeName = GenerateNodeName(NodeNames::moveRegister_);
  visitedNodeStack_.push_back(nodeName);

  command->Destination()->Accept(this);
  DoAddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  command->Source()->Accept(this);
  DoAddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();
}

void DotLangVisitor::Visit(const TempExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::temp_);
  visitedNodeStack_.push_back(nodeName);

  std::string tempNodeName = "\"" + GenerateNodeName("Temp") + ": ";
  tempNodeName += expression->Name() + "\"";
  DoAddEdge(nodeName, tempNodeName);
}

void DotLangVisitor::Visit(const AddCommand* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::add_);
  visitedNodeStack_.push_back(nodeName);

  expression->LeftOperand()->Accept(this);
  DoAddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  expression->RightOperand()->Accept(this);
  DoAddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();
}

void DotLangVisitor::Visit(const AddConstCommand* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::addConst_);
  visitedNodeStack_.push_back(nodeName);

  expression->GetExpression()->Accept(this);
  DoAddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  std::string valueNodeName = "\"" + GenerateNodeName("Value") + ": ";
  valueNodeName += std::to_string(expression->Constant()) + "\"";
  DoAddEdge(nodeName, valueNodeName);
}

void DotLangVisitor::Visit(const SubCommand* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::sub_);
  visitedNodeStack_.push_back(nodeName);

  expression->LeftOperand()->Accept(this);
  DoAddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  expression->RightOperand()->Accept(this);
  DoAddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();
}

void DotLangVisitor::Visit(const SubConstCommand* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::subConst_);
  visitedNodeStack_.push_back(nodeName);

  expression->GetExpression()->Accept(this);
  DoAddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  std::string valueNodeName = "\"" + GenerateNodeName("Value") + ": ";
  valueNodeName += std::to_string(expression->Constant()) + "\"";
  DoAddEdge(nodeName, valueNodeName);
}

void DotLangVisitor::Visit(const MultCommand* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::mult_);
  visitedNodeStack_.push_back(nodeName);

  expression->LeftOperand()->Accept(this);
  DoAddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  expression->RightOperand()->Accept(this);
  DoAddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();
}

void DotLangVisitor::Visit(const DivCommand* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::div_);
  visitedNodeStack_.push_back(nodeName);

  expression->LeftOperand()->Accept(this);
  DoAddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  expression->RightOperand()->Accept(this);
  DoAddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();
}

void DotLangVisitor::Visit(const LoadCommand* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::load_);
  visitedNodeStack_.push_back(nodeName);

  expression->Source()->Accept(this);
  DoAddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  std::string valueNodeName = "\"" + GenerateNodeName("Value") + ": ";
  valueNodeName += std::to_string(expression->Offset()) + "\"";
  DoAddEdge(nodeName, valueNodeName);
}

void DotLangVisitor::Visit(const NullExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::nullExp_);
  visitedNodeStack_.push_back(nodeName);
}

void DotLangVisitor::Visit(const ExpStatementCommand* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::expStat_);
  visitedNodeStack_.push_back(nodeName);

  statement->GetExpression()->Accept(this);
  DoAddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();
}

void DotLangVisitor::Visit(const StoreCommand* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::store_);
  visitedNodeStack_.push_back(nodeName);

  expression->Destination()->Accept(this);
  DoAddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  std::string valueNodeName = "\"" + GenerateNodeName("Value") + ": ";
  valueNodeName += std::to_string(expression->Offset()) + "\"";
  DoAddEdge(nodeName, valueNodeName);

  expression->Source()->Accept(this);
  DoAddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  DoAddEdge(nodeName, valueNodeName);
}
