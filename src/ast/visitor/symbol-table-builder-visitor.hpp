// Description: SymbolTableBuilderVisitor

#pragma once

#include <iostream>  // for verbose output
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <ast/node/node-names.hpp>
#include <ast/visitor/symbol-table.hpp>
#include <ast/visitor/visitor.hpp>
#include <utils/compilation-error.hpp>

#include <ast/node/access-modifier.hpp>
#include <ast/node/class-declaration-list.hpp>
#include <ast/node/class-declaration.hpp>
#include <ast/node/expression-list.hpp>
#include <ast/node/expression.hpp>
#include <ast/node/main-class.hpp>
#include <ast/node/method-argument-list.hpp>
#include <ast/node/method-argument.hpp>
#include <ast/node/method-declaration-list.hpp>
#include <ast/node/method-declaration.hpp>
#include <ast/node/program.hpp>
#include <ast/node/statement-list.hpp>
#include <ast/node/statement.hpp>
#include <ast/node/type-modifier.hpp>
#include <ast/node/var-declaration-list.hpp>
#include <ast/node/var-declaration.hpp>

namespace Ast {

using MethodNameToDefinitionMap =
    std::unordered_map<std::string, std::shared_ptr<const MethodDefinition>>;
using VarNameToTypeMap = std::unordered_map<std::string, TypeIdentifier>;
using ArgumentsTypesList = std::vector<TypeIdentifier>;

class SymbolTableBuilderVisitor : public Visitor {
 public:
  explicit SymbolTableBuilderVisitor(bool verbose = false)
      : Visitor(verbose),
        lastMethodDefinition_(nullptr),
        lastClassDefinition_(nullptr),
        methodDefinitions_(nullptr),
        table_(new SymbolTable()),
        errors_(new std::vector<CompilationError>()) {}

  const SymbolTable* GetSymbolTable() const;
  const std::vector<CompilationError>* Errors() const;

  // Visitors for different node types
  void Visit(const PublicAccessModifier* modifier) override;
  void Visit(const PrivateAccessModifier* modifier) override;

  void Visit(const BinaryExpression* expression) override;
  void Visit(const BracketExpression* expression) override;
  void Visit(const NumberExpression* expression) override;
  void Visit(const LogicExpression* expression) override;
  void Visit(const IdExpression* expression) override;
  void Visit(const LengthExpression* expression) override;
  void Visit(const MethodExpression* expression) override;
  void Visit(const ThisExpression* expression) override;
  void Visit(const NewArrayExpression* expression) override;
  void Visit(const NewIdExpression* expression) override;
  void Visit(const NegateExpression* expression) override;

  void Visit(const AssignIdStatement* statement) override;
  void Visit(const AssignIdWithIndexStatement* statement) override;
  void Visit(const PrintStatement* statement) override;
  void Visit(const ConditionalStatement* statement) override;
  void Visit(const WhileLoopStatement* statement) override;
  void Visit(const BracesStatement* statement) override;

  void Visit(const IntTypeModifier* typeModifier) override;
  void Visit(const BooleanTypeModifier* typeModifier) override;
  void Visit(const IntArrayTypeModifier* typeModifier) override;
  void Visit(const IdTypeModifier* typeModifier) override;

  void Visit(const VarDeclaration* declaration) override;
  void Visit(const MethodArgument* argument) override;
  void Visit(const MethodDeclaration* declaration) override;
  void Visit(const MainClass* mainClass) override;
  void Visit(const ClassDeclaration* declaration) override;
  void Visit(const Program* program) override;

  void Visit(const ExpressionList* list) override;
  void Visit(const StatementList* list) override;
  void Visit(const VarDeclarationList* list) override;
  void Visit(const MethodArgumentList* list) override;
  void Visit(const MethodDeclarationList* list) override;
  void Visit(const ClassDeclarationList* list) override;

 private:
  TypeIdentifier lastType_;
  AccessModifiers lastAccessModifier_;
  std::vector<std::string> lastId_;

  std::shared_ptr<const MethodDefinition> lastMethodDefinition_;
  std::shared_ptr<const ClassDefinition> lastClassDefinition_;

  std::vector<std::shared_ptr<VarNameToTypeMap>> localVariableTypes_;
  std::shared_ptr<ArgumentsTypesList> sortedArgumentsTypes_;

  std::shared_ptr<MethodNameToDefinitionMap> methodDefinitions_;

  SymbolTable* table_;
  std::vector<CompilationError>* errors_;
};

const SymbolTable* SymbolTableBuilderVisitor::GetSymbolTable() const {
  return table_;
}

const std::vector<CompilationError>* SymbolTableBuilderVisitor::Errors() const {
  return errors_;
}

/*__________ Access Modifiers __________*/

void SymbolTableBuilderVisitor::Visit(const PublicAccessModifier* modifier) {
  std::string nodeName = GenerateNodeName(NodeNames::accessModePublic_);
  OnNodeEnter(nodeName, modifier->GetLocation());

  lastAccessModifier_ = AccessModifiers::Public;

  OnNodeExit(nodeName, modifier->GetLocation());
}

void SymbolTableBuilderVisitor::Visit(const PrivateAccessModifier* modifier) {
  std::string nodeName = GenerateNodeName(NodeNames::accessModPrivate_);
  OnNodeEnter(nodeName, modifier->GetLocation());

  lastAccessModifier_ = AccessModifiers::Private;

  OnNodeExit(nodeName, modifier->GetLocation());
}

/*__________ Expressions __________*/

// ignored
void SymbolTableBuilderVisitor::Visit(const BinaryExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expBinary_);
  OnNodeEnter(nodeName, expression->GetLocation());

  OnNodeExit(nodeName, expression->GetLocation());
}

// ignored
void SymbolTableBuilderVisitor::Visit(const BracketExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expBracket_);
  OnNodeEnter(nodeName, expression->GetLocation());

  OnNodeExit(nodeName, expression->GetLocation());
}

// ignored
void SymbolTableBuilderVisitor::Visit(const NumberExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expNumber_);
  OnNodeEnter(nodeName, expression->GetLocation());

  OnNodeExit(nodeName, expression->GetLocation());
}

// ignored
void SymbolTableBuilderVisitor::Visit(const LogicExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expLogic_);
  OnNodeEnter(nodeName, expression->GetLocation());

  OnNodeExit(nodeName, expression->GetLocation());
}

void SymbolTableBuilderVisitor::Visit(const IdExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expId_);
  OnNodeEnter(nodeName, expression->GetLocation());

  lastId_.push_back(expression->Name());

  OnNodeExit(nodeName, expression->GetLocation());
}

// ignored
void SymbolTableBuilderVisitor::Visit(const LengthExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expLength_);
  OnNodeEnter(nodeName, expression->GetLocation());

  OnNodeExit(nodeName, expression->GetLocation());
}

// ignored
void SymbolTableBuilderVisitor::Visit(const MethodExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expMethod_);
  OnNodeEnter(nodeName, expression->GetLocation());

  OnNodeExit(nodeName, expression->GetLocation());
}

// ignored
void SymbolTableBuilderVisitor::Visit(const ThisExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expThis_);
  OnNodeEnter(nodeName, expression->GetLocation());

  OnNodeExit(nodeName, expression->GetLocation());
}

// ignored
void SymbolTableBuilderVisitor::Visit(const NewArrayExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expNewArray_);
  OnNodeEnter(nodeName, expression->GetLocation());

  OnNodeExit(nodeName, expression->GetLocation());
}

// ignored
void SymbolTableBuilderVisitor::Visit(const NewIdExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expNewId_);
  OnNodeEnter(nodeName, expression->GetLocation());

  OnNodeExit(nodeName, expression->GetLocation());
}

// ignored
void SymbolTableBuilderVisitor::Visit(const NegateExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expNegate_);
  OnNodeEnter(nodeName, expression->GetLocation());

  OnNodeExit(nodeName, expression->GetLocation());
}

/*__________ Statements __________*/

// ignored
void SymbolTableBuilderVisitor::Visit(const AssignIdStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statAssignId_);
  OnNodeEnter(nodeName, statement->GetLocation());

  OnNodeExit(nodeName, statement->GetLocation());
}

// ignored
void SymbolTableBuilderVisitor::Visit(
    const AssignIdWithIndexStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statAssignIdWithIndex_);
  OnNodeEnter(nodeName, statement->GetLocation());

  OnNodeExit(nodeName, statement->GetLocation());
}

// ignored
void SymbolTableBuilderVisitor::Visit(const PrintStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statPrint_);
  OnNodeEnter(nodeName, statement->GetLocation());

  OnNodeExit(nodeName, statement->GetLocation());
}

// ignored
void SymbolTableBuilderVisitor::Visit(const ConditionalStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statConditional_);
  OnNodeEnter(nodeName, statement->GetLocation());

  OnNodeExit(nodeName, statement->GetLocation());
}

// ignored
void SymbolTableBuilderVisitor::Visit(const WhileLoopStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statWhileLoop_);
  OnNodeEnter(nodeName, statement->GetLocation());

  OnNodeExit(nodeName, statement->GetLocation());
}

// ignored
void SymbolTableBuilderVisitor::Visit(const BracesStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statBraces_);
  OnNodeEnter(nodeName, statement->GetLocation());

  OnNodeExit(nodeName, statement->GetLocation());
}

/*__________ Type Modifiers __________*/

void SymbolTableBuilderVisitor::Visit(const IntTypeModifier* typeModifier) {
  std::string nodeName = GenerateNodeName(NodeNames::typeModInt_);
  OnNodeEnter(nodeName, typeModifier->GetLocation());

  lastType_ = TypeIdentifier(TypeIdentifieres::Int);

  OnNodeExit(nodeName, typeModifier->GetLocation());
}

void SymbolTableBuilderVisitor::Visit(const BooleanTypeModifier* typeModifier) {
  std::string nodeName = GenerateNodeName(NodeNames::typeModeBool_);
  OnNodeEnter(nodeName, typeModifier->GetLocation());

  lastType_ = TypeIdentifier(TypeIdentifieres::Boolean);

  OnNodeExit(nodeName, typeModifier->GetLocation());
}

void SymbolTableBuilderVisitor::Visit(
    const IntArrayTypeModifier* typeModifier) {
  std::string nodeName = GenerateNodeName(NodeNames::typeModIntArray_);
  OnNodeEnter(nodeName, typeModifier->GetLocation());

  lastType_ = TypeIdentifier(TypeIdentifieres::IntArray);

  OnNodeExit(nodeName, typeModifier->GetLocation());
}

void SymbolTableBuilderVisitor::Visit(const IdTypeModifier* typeModifier) {
  std::string nodeName = GenerateNodeName(NodeNames::typeModeId_);
  OnNodeEnter(nodeName, typeModifier->GetLocation());

  lastType_ = TypeIdentifier(typeModifier->TypeId()->Name());

  OnNodeExit(nodeName, typeModifier->GetLocation());
}

/*__________ Other (except lists) __________*/

void SymbolTableBuilderVisitor::Visit(const VarDeclaration* declaration) {
  std::string nodeName = GenerateNodeName(NodeNames::varDecl_);
  OnNodeEnter(nodeName, declaration->GetLocation());

  declaration->Type()->Accept(this);  // fills lastType
  declaration->Id()->Accept(this);    // fills lastId.back()

  OnNodeExit(nodeName, declaration->GetLocation());
}

void SymbolTableBuilderVisitor::Visit(const MethodArgument* argument) {
  std::string nodeName = GenerateNodeName(NodeNames::methArg_);
  OnNodeEnter(nodeName, argument->GetLocation());

  argument->Type()->Accept(this);  // fills lastType
  argument->Id()->Accept(this);    // fills lastId.back()

  OnNodeExit(nodeName, argument->GetLocation());
}

void SymbolTableBuilderVisitor::Visit(const MethodDeclaration* declaration) {
  std::string nodeName = GenerateNodeName(NodeNames::methDecl_);
  OnNodeEnter(nodeName, declaration->GetLocation());

  declaration->GetAccessModifier()->Accept(this);  // fills lastAccessModifier

  localVariableTypes_.push_back(
      std::shared_ptr<VarNameToTypeMap>(new VarNameToTypeMap()));
  sortedArgumentsTypes_ = std::make_shared<ArgumentsTypesList>();

  declaration->MethodArguments()->Accept(
      this);  // fills localVariableTypes.back()

  localVariableTypes_.push_back(
      std::shared_ptr<VarNameToTypeMap>(new VarNameToTypeMap()));
  declaration->VarDeclarations()->Accept(
      this);  // fills localVariableTypes.back()

  declaration->GetTypeModifier()->Accept(this);  // fills lastType

  declaration->MethodId()->Accept(this);  // fills lastId.back()

  lastMethodDefinition_ = std::make_shared<MethodDefinition>(
      lastAccessModifier_, lastId_.back(), lastType_,
      localVariableTypes_.at(localVariableTypes_.size() - 2),
      sortedArgumentsTypes_, localVariableTypes_.back());

  sortedArgumentsTypes_ = nullptr;

  OnNodeExit(nodeName, declaration->GetLocation());
}

void SymbolTableBuilderVisitor::Visit(const MainClass* mainClass) {
  std::string nodeName = GenerateNodeName(NodeNames::mainClass_);
  OnNodeEnter(nodeName, mainClass->GetLocation());

  lastId_.clear();
  mainClass->ClassName()->Accept(this);  // fills lastId[0]

  methodDefinitions_ = std::shared_ptr<MethodNameToDefinitionMap>(
      new MethodNameToDefinitionMap());
  lastMethodDefinition_ = std::make_shared<MethodDefinition>(
      AccessModifiers::Public, "main",
      TypeIdentifier(
          TypeIdentifieres::Int),  // we do not have `void`, let it be `int`
      std::shared_ptr<VarNameToTypeMap>(
          new VarNameToTypeMap()),  // no arguments
      std::make_shared<ArgumentsTypesList>(),
      std::shared_ptr<VarNameToTypeMap>(
          new VarNameToTypeMap())  // no local variables
  );
  auto res = methodDefinitions_->insert(std::make_pair(
      lastMethodDefinition_->MethodName(), lastMethodDefinition_));
  if (!res.second) {
    errors_->push_back(CompilationError(mainClass->GetLocation(),
                                        CompilationError::redefinitionMethid_));
  }

  std::shared_ptr<VarNameToTypeMap> localVariables(new VarNameToTypeMap());
  lastClassDefinition_ = std::make_shared<ClassDefinition>(
      lastId_[0], methodDefinitions_, localVariables);

  OnNodeExit(nodeName, mainClass->GetLocation());
}

void SymbolTableBuilderVisitor::Visit(const ClassDeclaration* declaration) {
  std::string nodeName = GenerateNodeName(NodeNames::classDecl_);
  OnNodeEnter(nodeName, declaration->GetLocation());

  lastId_.clear();
  declaration->ClassName()->Accept(this);  // fills lastId[0]

  localVariableTypes_ = std::vector<std::shared_ptr<VarNameToTypeMap>>{
      std::shared_ptr<VarNameToTypeMap>(new VarNameToTypeMap())};
  declaration->VarDeclarations()->Accept(this);  // fills localVariableTypes[0]

  methodDefinitions_ = std::shared_ptr<MethodNameToDefinitionMap>(
      new MethodNameToDefinitionMap());
  declaration->MethodDeclarations()->Accept(this);  // fills methodDefinitions

  if (declaration->HasParent()) {
    declaration->ExtendsClassName()->Accept(this);  // fills lastId.back()
    lastClassDefinition_ = std::make_shared<ClassDefinition>(
        lastId_[0], lastId_.back(), methodDefinitions_, localVariableTypes_[0]);
  } else {
    lastClassDefinition_ = std::make_shared<ClassDefinition>(
        lastId_[0], methodDefinitions_, localVariableTypes_[0]);
  }

  OnNodeExit(nodeName, declaration->GetLocation());
}

void SymbolTableBuilderVisitor::Visit(const Program* program) {
  std::string nodeName = GenerateNodeName(NodeNames::program_);
  OnNodeEnter(nodeName, program->GetLocation());

  program->GetMainClass()->Accept(this);
  bool isAdded = table_->AddClassDefinition(lastClassDefinition_->ClassName(),
                                            lastClassDefinition_);
  if (!isAdded) {
    errors_->push_back(CompilationError(program->GetMainClass()->GetLocation(),
                                        CompilationError::redefinitionClass_));
  }

  program->ClassDeclarations()->Accept(this);

  OnNodeExit(nodeName, program->GetLocation());
}

/*__________  Lists __________*/
// ignored
void SymbolTableBuilderVisitor::Visit(const ExpressionList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::expList_);
  OnNodeEnter(nodeName, list->GetLocation());

  OnNodeExit(nodeName, list->GetLocation());
}

// ignored
void SymbolTableBuilderVisitor::Visit(const StatementList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::statList_);
  OnNodeEnter(nodeName, list->GetLocation());

  OnNodeExit(nodeName, list->GetLocation());
}

void SymbolTableBuilderVisitor::Visit(const VarDeclarationList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::varDeclList_);
  OnNodeEnter(nodeName, list->GetLocation());

  const std::vector<std::unique_ptr<const VarDeclaration>>& varDeclarations =
      list->VarDeclarations();
  for (auto it = varDeclarations.begin(); it != varDeclarations.end(); ++it) {
    (*it)->Accept(this);  // fills lastId.back() and lastType
    auto res = localVariableTypes_.back()->insert(
        std::make_pair(lastId_.back(), lastType_));
    if (!res.second) {
      errors_->push_back(CompilationError(
          (*it)->GetLocation(), CompilationError::redefinitionLocalVar_));
    }
  }

  OnNodeExit(nodeName, list->GetLocation());
}

void SymbolTableBuilderVisitor::Visit(const MethodArgumentList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::methAgrList_);
  OnNodeEnter(nodeName, list->GetLocation());

  const std::vector<std::unique_ptr<const MethodArgument>>& methodArguments =
      list->MethodArguments();
  for (auto it = methodArguments.begin(); it != methodArguments.end(); ++it) {
    (*it)->Accept(this);  // fills lastId.back() and lastType
    auto res = localVariableTypes_.back()->insert(
        std::make_pair(lastId_.back(), lastType_));
    sortedArgumentsTypes_->push_back(lastType_);
    if (!res.second) {
      errors_->push_back(CompilationError(
          (*it)->GetLocation(), CompilationError::redefinitionLocalVar_));
    }
  }

  OnNodeExit(nodeName, list->GetLocation());
}

void SymbolTableBuilderVisitor::Visit(const MethodDeclarationList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::methDeclList_);
  OnNodeEnter(nodeName, list->GetLocation());

  const std::vector<std::unique_ptr<const MethodDeclaration>>&
      methodDeclarations = list->MethodDeclarations();
  for (auto it = methodDeclarations.begin(); it != methodDeclarations.end();
       ++it) {
    (*it)->Accept(this);
    auto res = methodDefinitions_->insert(std::make_pair(
        lastMethodDefinition_->MethodName(), lastMethodDefinition_));
    if (!res.second) {
      errors_->push_back(CompilationError(
          (*it)->GetLocation(), CompilationError::redefinitionMethid_));
    }
  }

  OnNodeExit(nodeName, list->GetLocation());
}

void SymbolTableBuilderVisitor::Visit(const ClassDeclarationList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::classDeclList_);
  OnNodeEnter(nodeName, list->GetLocation());

  const std::vector<std::unique_ptr<const ClassDeclaration>>&
      classDeclarations = list->ClassDeclarations();
  for (auto it = classDeclarations.begin(); it != classDeclarations.end();
       ++it) {
    (*it)->Accept(this);
    bool isAdded = table_->AddClassDefinition(lastClassDefinition_->ClassName(),
                                              lastClassDefinition_);
    if (!isAdded) {
      errors_->push_back(CompilationError(
          (*it)->GetLocation(), CompilationError::redefinitionClass_));
    }
  }

  OnNodeExit(nodeName, list->GetLocation());
}

}  // namespace Ast
