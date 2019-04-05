#pragma once

#include <memory>
#include <optional>
#include "../../../irt/frame/code-fragment.hpp"
#include "../../../irt/wrapper/wrapper.hpp"
#include "../../../utils/ast.hpp"
#include "../../../utils/irt.hpp"
#include "../symbol-table/symbol-table.hpp"
#include "../visitor.hpp"

namespace Ast {

class Translator : public Visitor {
 private:
  enum class VariableContext { ClassVariable, MethodVariable, MethodArgument };

 public:
  Translator();

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

  std::shared_ptr<Irt::CodeFragment> GetCodeFragment();

 private:
  std::optional<Irt::ArithmeticOperator> ToIrtArithmeticOperator(
      BinaryOperator binaryOperator);

  std::shared_ptr<Irt::Expression> Allocate(
      std::shared_ptr<Irt::Expression> wordsCount);

  std::shared_ptr<Irt::Expression> GetVariable(const std::string &name);

 private:
  std::shared_ptr<Irt::Wrapper> wrapper_;
  std::shared_ptr<Irt::Statement> statement_;
  std::shared_ptr<Irt::CodeFragment> codeFragment_;
  SymbolTable symbolTable_;
  std::string className_;
  std::string methodName_;
  VariableContext variableContext_;
};

}  // namespace Ast
