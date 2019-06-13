#pragma once

#include <iostream>  // for verbose output
#include <string>
#include <unordered_map>
#include <vector>

namespace Ast {

class PublicAccessModifier;
class PrivateAccessModifier;

class BinaryExpression;
class BracketExpression;
class NumberExpression;
class LogicExpression;
class IdExpression;
class LengthExpression;
class MethodExpression;
class ThisExpression;
class NewArrayExpression;
class NewIdExpression;
class NegateExpression;

class AssignIdStatement;
class AssignIdWithIndexStatement;
class PrintStatement;
class ConditionalStatement;
class WhileLoopStatement;
class BracesStatement;

class IntTypeModifier;
class BooleanTypeModifier;
class IntArrayTypeModifier;
class IdTypeModifier;

class VarDeclaration;
class MethodArgument;
class MethodDeclaration;
class MainClass;
class ClassDeclaration;
class Program;

class ExpressionList;
class StatementList;
class VarDeclarationList;
class MethodArgumentList;
class MethodDeclarationList;
class ClassDeclarationList;

struct Location;

class IVisitor {
 public:
  virtual ~IVisitor() = default;
  virtual void Visit(const PublicAccessModifier* modifier) = 0;
  virtual void Visit(const PrivateAccessModifier* modifier) = 0;

  virtual void Visit(const BinaryExpression* expression) = 0;
  virtual void Visit(const BracketExpression* expression) = 0;
  virtual void Visit(const NumberExpression* expression) = 0;
  virtual void Visit(const LogicExpression* expression) = 0;
  virtual void Visit(const IdExpression* expression) = 0;
  virtual void Visit(const LengthExpression* expression) = 0;
  virtual void Visit(const MethodExpression* expression) = 0;
  virtual void Visit(const ThisExpression* expression) = 0;
  virtual void Visit(const NewArrayExpression* expression) = 0;
  virtual void Visit(const NewIdExpression* expression) = 0;
  virtual void Visit(const NegateExpression* expression) = 0;

  virtual void Visit(const AssignIdStatement* statement) = 0;
  virtual void Visit(const AssignIdWithIndexStatement* statement) = 0;
  virtual void Visit(const PrintStatement* statement) = 0;
  virtual void Visit(const ConditionalStatement* statement) = 0;
  virtual void Visit(const WhileLoopStatement* statement) = 0;
  virtual void Visit(const BracesStatement* statement) = 0;

  virtual void Visit(const IntTypeModifier* typeModifier) = 0;
  virtual void Visit(const BooleanTypeModifier* typeModifier) = 0;
  virtual void Visit(const IntArrayTypeModifier* typeModifier) = 0;
  virtual void Visit(const IdTypeModifier* typeModifier) = 0;

  virtual void Visit(const VarDeclaration* declaration) = 0;
  virtual void Visit(const MethodArgument* argument) = 0;
  virtual void Visit(const MethodDeclaration* declaration) = 0;
  virtual void Visit(const MainClass* mainClass) = 0;
  virtual void Visit(const ClassDeclaration* declaration) = 0;
  virtual void Visit(const Program* program) = 0;

  virtual void Visit(const ExpressionList* list) = 0;
  virtual void Visit(const StatementList* list) = 0;
  virtual void Visit(const VarDeclarationList* list) = 0;
  virtual void Visit(const MethodArgumentList* list) = 0;
  virtual void Visit(const MethodDeclarationList* list) = 0;
  virtual void Visit(const ClassDeclarationList* list) = 0;
};

enum class OperatorTypes : char;

class Visitor : public IVisitor {
 public:
  explicit Visitor(bool verbose) : verbose_(verbose) {}

 protected:
  // Generates unique id for nodes of one type.
  int GenerateNodeNextIndex(const std::string& nodeType);

  // Generates full node name based on the node type and a unique id assigned to
  // the node.
  std::string GenerateNodeName(const std::string& nodeTypeName);

  // Is called every time a visitor enters a node
  virtual void OnNodeEnter(const std::string& nodeName,
                           const Location& location);
  // Is called every time a visitor is about to exit a node
  virtual void OnNodeExit(const std::string& nodeName,
                          const Location& location);

  // Maps each TOperatorType to a string with its name.
  std::string OperatorName(const OperatorTypes& type) const;

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

}  // namespace Ast
