#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "../../../utils/ast.hpp"
#include "../../../utils/compile-error/compile-error.hpp"
#include "../visitor.hpp"
#include "class-info.hpp"
#include "method-info.hpp"
#include "variable-info.hpp"

namespace Ast {

class SymbolTable : public Visitor {
 private:
  using TypeVariant = std::variant<TypeKind, std::string>;

 public:
  ~SymbolTable() = default;

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

  std::vector<CompileError> GetErrorList() const;

  const std::unordered_map<std::string, ClassInfo> &GetClasses() const;

  int GetVariableOffset(const std::string &className,
                        const std::string &variableName);

 private:
  void ForwardVisit(MainClass *node);

  void ForwardVisit(ClassDeclaration *node);

  void ForwardVisit(ClassBody *node);

  void ForwardVisit(VarDeclaration *node);

  void ForwardVisit(MethodDeclaration *node);

  void ForwardVisit(MethodBody *node);

  void CompareTypes(TypeVariant lhs, TypeVariant rhs, const Location &location);

  bool IsBaseOf(const std::string &baseClassName,
                const std::string &derivedClassName) const;

  std::optional<VariableInfo> TryLookUpVariable(const ClassInfo &currentClass,
                                                const std::string &name,
                                                const Location &location,
                                                bool inBaseClass);

  std::optional<MethodInfo> TryLookUpMethod(const ClassInfo &currentClass,
                                            const std::string &name,
                                            const Location &location);

  bool CheckIfUndeclared(TypeVariant type, const Location &location);

  void UpdateVariableOffsets(const std::string &name);

 private:
  std::unordered_map<std::string, ClassInfo> classes_;
  std::pair<std::string, VariableInfo> currentVariable_;
  std::pair<std::string, MethodInfo> currentMethod_;
  std::pair<std::string, ClassInfo> currentClass_;
  std::vector<CompileError> errors_;
};

}  // namespace Ast
