#pragma once

#include <fstream>
#include <string>
#include "../../../utils/ast.hpp"
#include "../visitor.hpp"

namespace Ast {

class Printer : public Visitor {
 public:
  explicit Printer(const std::string &filename);

  ~Printer();

  void Visit(AssignmentByIndexStatement *node) final;

  void Visit(AssignmentStatement *node) final;

  void Visit(BinaryOperatorExpression *node) final;

  void Visit(BooleanExpression *node) final;

  void Visit(ClassBody *node) final;

  void Visit(ClassDeclaration *node) final;

  void Visit(ConditionStatement *node) final;

  void Visit(IdentifierExpression *node) final;

  void Visit(IndexExpression *node) final;

  void Visit(IntArrayConstructorExpression *node) final;

  void Visit(LengthExpression *node) final;

  void Visit(LoopStatement *node) final;

  void Visit(MainClass *node) final;

  void Visit(MethodBody *node) final;

  void Visit(MethodCallExpression *node) final;

  void Visit(MethodDeclaration *node) final;

  void Visit(NotExpression *node) final;

  void Visit(NumberExpression *node) final;

  void Visit(PrintStatement *node) final;

  void Visit(Program *node) final;

  void Visit(ScopeStatement *node) final;

  void Visit(ThisExpression *node) final;

  void Visit(Type *node) final;

  void Visit(UserTypeConstructorExpression *node) final;

  void Visit(VarDeclaration *node) final;

 private:
  void PrintHead(int headNodeNumber, const std::string &label);

  void PrintEdge(int headNodeNumber);

  void PrintLeaf(int headNodeNumber, const std::string &label,
                 const std::string &name);

 private:
  std::ofstream file_;
  int nodeNumber_;
};

}  // namespace Ast
