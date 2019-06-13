#pragma once

#include <iostream>  // for verbose output
#include <string>
#include <unordered_map>
#include <vector>

namespace Irt {

class ConstExpression;
class NameExpression;
class TempExpression;
class BinaryExpression;
class MemExpression;
class CallExpression;
class EseqExpression;

class ExpStatement;
class JumpConditionalStatement;
class JumpStatement;
class LabelStatement;
class MoveStatement;
class SeqStatement;

class ExpressionList;
class StatementList;

class IVisitor {
 public:
  virtual ~IVisitor() {}

  virtual void Visit(const ConstExpression* expression) = 0;
  virtual void Visit(const NameExpression* expression) = 0;
  virtual void Visit(const TempExpression* expression) = 0;
  virtual void Visit(const BinaryExpression* expression) = 0;
  virtual void Visit(const MemExpression* expression) = 0;
  virtual void Visit(const CallExpression* expression) = 0;
  virtual void Visit(const EseqExpression* expression) = 0;

  virtual void Visit(const ExpStatement* statement) = 0;
  virtual void Visit(const JumpConditionalStatement* statement) = 0;
  virtual void Visit(const JumpStatement* statement) = 0;
  virtual void Visit(const LabelStatement* statement) = 0;
  virtual void Visit(const MoveStatement* statement) = 0;
  virtual void Visit(const SeqStatement* statement) = 0;

  virtual void Visit(const ExpressionList* list) = 0;
  virtual void Visit(const StatementList* list) = 0;
};

enum class OperatorTypes : char;
enum class LogicOperatorTypes : char;

class Visitor : public IVisitor {
 public:
  Visitor(bool verbose) : verbose_(verbose) {}
  virtual ~Visitor() {}

 protected:
  // Generates unique id for nodes of one type.
  int GenerateNodeNextIndex(const std::string& nodeType);

  // Generates full node name based on the node type and a unique id assigned to
  // the node.
  std::string GenerateNodeName(const std::string& nodeTypeName);

  // Is called every time visitor enters a node
  void OnNodeEnter(const std::string& nodeName);
  // Is called every time visitor is about to exit a node
  void OnNodeExit(const std::string& nodeName);

  // Maps each TOperatorType to a string with its name.
  std::string OperatorName(const OperatorTypes& type) const;
  // Maps each TLogicOperatorType to a string with its name.
  std::string OperatorName(const LogicOperatorTypes& type) const;

  // Maps each TOperatorType to a string with its character.
  std::string OperatorChar(const OperatorTypes& type) const;

  // used for generating unique node names
  std::unordered_map<std::string, int> nodeTypeLastUsedIndex_;

  // used for verbose output while traversing the tree
  bool verbose_;
  const std::string nodeEnterMarker_ = "in: ";
  const std::string nodeExitMarker_ = "out: ";
  std::string margin_;
};

}  // namespace Irt
