#pragma once

#include <iostream>  // for verbose output
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <irt/node/node-names.hpp>
#include <irt/visitor/visitor.hpp>

#include <irt/node/expression-list.hpp>
#include <irt/node/expression.hpp>
#include <irt/node/statement.hpp>

namespace Irt {

class DotLangVisitor : public Visitor {
 public:
  DotLangVisitor(bool verbose = false) : Visitor(verbose) {}
  ~DotLangVisitor() {}
  // Generates a string, representing the last traversal of the tree, in the DOT
  // Language. The DOT Language is the one supported by GraphViz.
  std::string GetTraversalInDotLanguage() const;

  // Resets the initial state of the object.
  // Should be used before every tree traversal (except the first one).
  void Clear();

  // Visitors for different node types.
  void Visit(const ConstExpression* expression) override;
  void Visit(const NameExpression* expression) override;
  void Visit(const TempExpression* expression) override;
  void Visit(const BinaryExpression* expression) override;
  void Visit(const MemExpression* expression) override;
  void Visit(const CallExpression* expression) override;
  void Visit(const EseqExpression* expression) override;

  void Visit(const ExpStatement* statement) override;
  void Visit(const JumpConditionalStatement* statement) override;
  void Visit(const JumpStatement* statement) override;
  void Visit(const LabelStatement* statement) override;
  void Visit(const MoveStatement* statement) override;
  void Visit(const SeqStatement* statement) override;

  void Visit(const ExpressionList* list) override;
  void Visit(const StatementList* list) override;

 private:
  std::unordered_map<std::string, std::vector<std::string>> treeEdges_;
  // used to track the traverse and collect some information
  std::vector<std::string> visitedNodeStack_;

  // Adds edge (nodeFromName; nodeToName) to treeEdges.
  void AddEdge(const std::string& nodeFromName, const std::string& nodeToName);
};

void DotLangVisitor::AddEdge(const std::string& nodeFromName,
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

void DotLangVisitor::Clear() {
  treeEdges_.clear();
  nodeTypeLastUsedIndex_.clear();
  visitedNodeStack_.clear();
}

/*__________ Expressions __________*/

void DotLangVisitor::Visit(const ConstExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expConst_);
  OnNodeEnter(nodeName);
  visitedNodeStack_.push_back(nodeName);

  std::string valueNodeName = "\"" + GenerateNodeName("Value") + ": ";
  valueNodeName += std::to_string(expression->Value()) + "\"";
  AddEdge(nodeName, valueNodeName);

  OnNodeExit(nodeName);
}

void DotLangVisitor::Visit(const NameExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expName_);
  OnNodeEnter(nodeName);
  visitedNodeStack_.push_back(nodeName);

  std::string valueNodeName = "\"" + GenerateNodeName("Label") + ": ";
  valueNodeName += expression->GetAddress().ToString() + "\"";
  AddEdge(nodeName, valueNodeName);

  OnNodeExit(nodeName);
}

void DotLangVisitor::Visit(const TempExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expTemp_);
  OnNodeEnter(nodeName);

  visitedNodeStack_.push_back(nodeName);

  std::string valueNodeName = "\"" + GenerateNodeName("Temp") + ": ";
  valueNodeName += expression->GetStorage().ToString() + "\"";
  AddEdge(nodeName, valueNodeName);

  OnNodeExit(nodeName);
}

void DotLangVisitor::Visit(const BinaryExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expBinary_);
  OnNodeEnter(nodeName);
  visitedNodeStack_.push_back(nodeName);

  expression->LeftOperand()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  AddEdge(nodeName, GenerateNodeName(OperatorName(expression->Operation())));

  expression->RightOperand()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName);
}

void DotLangVisitor::Visit(const MemExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expMem_);
  OnNodeEnter(nodeName);
  visitedNodeStack_.push_back(nodeName);

  expression->Address()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName);
}

void DotLangVisitor::Visit(const CallExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expCall_);
  OnNodeEnter(nodeName);
  visitedNodeStack_.push_back(nodeName);

  expression->Function()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  expression->Arguments()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName);
}

void DotLangVisitor::Visit(const EseqExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expEseq_);
  OnNodeEnter(nodeName);
  visitedNodeStack_.push_back(nodeName);

  expression->GetStatement()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  expression->GetExpression()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName);
}

/*__________ Statements __________*/

void DotLangVisitor::Visit(const ExpStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statExp_);
  OnNodeEnter(nodeName);
  visitedNodeStack_.push_back(nodeName);

  statement->GetExpression()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName);
}

void DotLangVisitor::Visit(const JumpConditionalStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statCJump_);
  OnNodeEnter(nodeName);
  visitedNodeStack_.push_back(nodeName);

  AddEdge(nodeName, GenerateNodeName(OperatorName(statement->Operation())));

  statement->LeftOperand()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  statement->RightOperand()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  std::string labelTrueNodeName = "\"" + GenerateNodeName("Label") + ": ";
  labelTrueNodeName += statement->TrueLabel().ToString() + "\"";
  AddEdge(nodeName, labelTrueNodeName);

  std::string labelFalseNodeName = "\"" + GenerateNodeName("Label") + ": ";
  labelFalseNodeName += statement->FalseLabel().ToString() + "\"";
  AddEdge(nodeName, labelFalseNodeName);

  OnNodeExit(nodeName);
}

void DotLangVisitor::Visit(const JumpStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statJump_);
  OnNodeEnter(nodeName);
  visitedNodeStack_.push_back(nodeName);

  std::string valueNodeName = "\"" + GenerateNodeName("Label") + ": ";
  valueNodeName += statement->Target().ToString() + "\"";
  AddEdge(nodeName, valueNodeName);

  OnNodeExit(nodeName);
}

void DotLangVisitor::Visit(const LabelStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statLabel_);
  OnNodeEnter(nodeName);
  visitedNodeStack_.push_back(nodeName);

  std::string valueNodeName = "\"" + GenerateNodeName("Label") + ": ";
  valueNodeName += statement->Label().ToString() + "\"";
  AddEdge(nodeName, valueNodeName);

  OnNodeExit(nodeName);
}

void DotLangVisitor::Visit(const MoveStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statMove_);
  OnNodeEnter(nodeName);
  visitedNodeStack_.push_back(nodeName);

  statement->Destination()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  statement->Source()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName);
}

void DotLangVisitor::Visit(const SeqStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statSeq_);
  OnNodeEnter(nodeName);
  visitedNodeStack_.push_back(nodeName);

  statement->LeftStatement()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  statement->RightStatement()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName);
}

/*__________  Lists __________*/

void DotLangVisitor::Visit(const ExpressionList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::listExp_);
  OnNodeEnter(nodeName);
  visitedNodeStack_.push_back(nodeName);

  const std::vector<std::unique_ptr<const Expression>>& expressions =
      list->Expressions();
  for (auto it = expressions.begin(); it != expressions.end(); ++it) {
    (*it)->Accept(this);

    AddEdge(nodeName, visitedNodeStack_.back());
    visitedNodeStack_.pop_back();
  }

  OnNodeExit(nodeName);
}

void DotLangVisitor::Visit(const StatementList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::listStat_);
  OnNodeEnter(nodeName);

  visitedNodeStack_.push_back(nodeName);

  const std::vector<std::unique_ptr<const Statement>>& statements =
      list->Statements();
  for (auto it = statements.begin(); it != statements.end(); ++it) {
    (*it)->Accept(this);

    AddEdge(nodeName, visitedNodeStack_.back());
    visitedNodeStack_.pop_back();
  }

  OnNodeExit(nodeName);
}

}  // namespace Irt
