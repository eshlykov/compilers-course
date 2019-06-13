#pragma once

#include <cg/visitor/assembly-command.hpp>
#include <cg/visitor/visitor.hpp>
#include <map>
#include <string>
#include <vector>

namespace Cg {

class CommandEmitterVisitor : public Visitor {
 public:
  using Visitor::Visitor;
  CommandEmitterVisitor();
  virtual ~CommandEmitterVisitor() {}

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

  const std::vector<AssemblyCommand>& Result() const { return code_; }

 private:
  std::string lastRegisterValue_;
  std::vector<AssemblyCommand> code_;

  std::map<std::string, std::string> tempToRegister_;
};

};  // namespace Cg
