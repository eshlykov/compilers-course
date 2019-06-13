#pragma once

#include <string>
#include <unordered_map>

namespace Cg {

class AddCommand;
class AddConstCommand;
class SubCommand;
class SubConstCommand;
class MultCommand;
class DivCommand;
class LoadCommand;
class StoreCommand;
class NullExpression;
class TempExpression;
class MoveRegisterCommand;
class LabelDeclarationCommand;
class CallFunctionCommand;
class JumpCommand;
class ConditionalJumpCommand;
class ExpStatementCommand;

class IVisitor {
 public:
  virtual ~IVisitor() {}

  virtual void Visit(const ConditionalJumpCommand* command) = 0;
  virtual void Visit(const JumpCommand* command) = 0;
  virtual void Visit(const CallFunctionCommand* command) = 0;
  virtual void Visit(const LabelDeclarationCommand* command) = 0;
  virtual void Visit(const MoveRegisterCommand* command) = 0;
  virtual void Visit(const TempExpression* expression) = 0;
  virtual void Visit(const AddCommand* expression) = 0;
  virtual void Visit(const AddConstCommand* expression) = 0;
  virtual void Visit(const SubCommand* expression) = 0;
  virtual void Visit(const SubConstCommand* expression) = 0;
  virtual void Visit(const MultCommand* expression) = 0;
  virtual void Visit(const DivCommand* expression) = 0;
  virtual void Visit(const LoadCommand* expression) = 0;
  virtual void Visit(const StoreCommand* expression) = 0;
  virtual void Visit(const NullExpression* expression) = 0;
  virtual void Visit(const ExpStatementCommand* statement) = 0;
};

class Visitor : public IVisitor {
 public:
  explicit Visitor(bool verbose) : verbose_(verbose) {}

  ~Visitor() override = default;

  // Generates unique id for nodes of one type.
  int GenerateNodeNextIndex(const std::string& nodeType) {
    int result = 0;
    auto insertResult =
        nodeTypeLastUsedIndex_.insert(std::make_pair(nodeType, result));
    if (!insertResult.second) {
      result = ++insertResult.first->second;
    }
    return result;
  }

  // Generates full node name based on the node type and a unique id assigned to
  // the node.
  std::string GenerateNodeName(const std::string& nodeTypeName) {
    return nodeTypeName + std::to_string(GenerateNodeNextIndex(nodeTypeName));
  }

 protected:
  bool verbose_;
  // used for generating unique node names
  std::unordered_map<std::string, int> nodeTypeLastUsedIndex_;
};

}  // namespace Cg
