#pragma once

#include <cg/visitor/visitor.hpp>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Cg {

class DotLangVisitor : public Visitor {
 public:
  using Visitor::Visitor;
  virtual ~DotLangVisitor() {}

  // Generates a string, representing the last traversal of the tree, in the DOT
  // Language. The DOT Language is the one supported by GraphViz.
  std::string GetTraversalInDotLanguage() const;

  void Visit(const ConditionalJumpCommand* command) override;
  void Visit(const JumpCommand* command) override;
  void Visit(const CallFunctionCommand* command) override;
  void Visit(const LabelDeclarationCommand* command) override;
  void Visit(const MoveRegisterCommand* command) override;
  void Visit(const TempExpression* expression) override;
  void Visit(const AddCommand* expression) override;
  void Visit(const AddConstCommand* expression) override;
  void Visit(const SubCommand* expression) override;
  void Visit(const SubConstCommand* expression) override;
  void Visit(const MultCommand* expression) override;
  void Visit(const DivCommand* expression) override;
  void Visit(const LoadCommand* expression) override;
  void Visit(const StoreCommand* expression) override;
  void Visit(const NullExpression* expression) override;
  void Visit(const ExpStatementCommand* statement) override;

 private:
  std::unordered_map<std::string, std::vector<std::string>> treeEdges_;
  // used to track the traverse and collect some information
  std::vector<std::string> visitedNodeStack_;

  // Adds edge (nodeFromName; nodeToName) to treeEdges.
  void DoAddEdge(const std::string& nodeFromName,
                 const std::string& nodeToName);
};

};  // namespace Cg
