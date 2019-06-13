#pragma once

#include <iostream>  // for verbose output
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <ast/node/node-names.hpp>
#include <ast/visitor/visitor.hpp>

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

class DotLangVisitor : public Visitor {
 public:
  explicit DotLangVisitor(bool verbose = false) : Visitor(verbose) {}
  // Generates a string, representing the last traversal of the tree, in the DOT
  // Language. The DOT Language is the one supported by GraphViz.
  std::string GetTraversalInDotLanguage() const;

  // Resets the initial state of the object.
  // Should be used before every tree traversal (except the first one).
  void Clear();

  // Visitors for different node types.
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

/*__________ Access Modifiers __________*/

void DotLangVisitor::Visit(const PublicAccessModifier* modifier) {
  std::string nodeName = GenerateNodeName(NodeNames::accessModePublic_);
  OnNodeEnter(nodeName, modifier->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  OnNodeExit(nodeName, modifier->GetLocation());
}

void DotLangVisitor::Visit(const PrivateAccessModifier* modifier) {
  std::string nodeName = GenerateNodeName(NodeNames::accessModPrivate_);
  OnNodeEnter(nodeName, modifier->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  OnNodeExit(nodeName, modifier->GetLocation());
}

/*__________ Expressions __________*/

void DotLangVisitor::Visit(const BinaryExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expBinary_);
  OnNodeEnter(nodeName, expression->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  expression->LeftOperand()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  AddEdge(nodeName, GenerateNodeName(OperatorName(expression->Operation())));

  expression->RightOperand()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName, expression->GetLocation());
}

void DotLangVisitor::Visit(const BracketExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expBracket_);
  OnNodeEnter(nodeName, expression->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  expression->ContainerExpression()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  expression->IndexExpression()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName, expression->GetLocation());
}

void DotLangVisitor::Visit(const NumberExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expNumber_);
  OnNodeEnter(nodeName, expression->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  std::string valueNodeName = "\"" + GenerateNodeName("Value") + ": ";
  valueNodeName += std::to_string(expression->Value()) + "\"";
  AddEdge(nodeName, valueNodeName);

  OnNodeExit(nodeName, expression->GetLocation());
}

void DotLangVisitor::Visit(const LogicExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expLogic_);
  OnNodeEnter(nodeName, expression->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  std::string valueNodeName = "\"" + GenerateNodeName("Value") + ": ";
  valueNodeName += std::string(expression->Value() ? "true" : "false") + '\"';
  AddEdge(nodeName, valueNodeName);

  OnNodeExit(nodeName, expression->GetLocation());
}

void DotLangVisitor::Visit(const IdExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expId_);
  OnNodeEnter(nodeName, expression->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  std::string valueNodeName =
      "\"" + GenerateNodeName("Id") + ": " + expression->Name() + "\"";
  AddEdge(nodeName, valueNodeName);

  OnNodeExit(nodeName, expression->GetLocation());
}

void DotLangVisitor::Visit(const LengthExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expLength_);
  OnNodeEnter(nodeName, expression->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  expression->LengthTarget()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName, expression->GetLocation());
}

void DotLangVisitor::Visit(const MethodExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expMethod_);
  OnNodeEnter(nodeName, expression->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  expression->CallerExpression()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  expression->MethodId()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  expression->Arguments()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName, expression->GetLocation());
}

void DotLangVisitor::Visit(const ThisExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expThis_);
  OnNodeEnter(nodeName, expression->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  OnNodeExit(nodeName, expression->GetLocation());
}

void DotLangVisitor::Visit(const NewArrayExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expNewArray_);
  OnNodeEnter(nodeName, expression->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  expression->LengthExpression()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName, expression->GetLocation());
}

void DotLangVisitor::Visit(const NewIdExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expNewId_);
  OnNodeEnter(nodeName, expression->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  expression->TargetId()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName, expression->GetLocation());
}

void DotLangVisitor::Visit(const NegateExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expNegate_);
  OnNodeEnter(nodeName, expression->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  expression->TargetExpression()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName, expression->GetLocation());
}

/*__________ Statements __________*/

void DotLangVisitor::Visit(const AssignIdStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statAssignId_);
  OnNodeEnter(nodeName, statement->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  statement->LeftPart()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  statement->RightPart()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName, statement->GetLocation());
}

void DotLangVisitor::Visit(const AssignIdWithIndexStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statAssignIdWithIndex_);
  OnNodeEnter(nodeName, statement->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  statement->LeftPartId()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  statement->LeftPartIndex()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  statement->RightPart()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName, statement->GetLocation());
}

void DotLangVisitor::Visit(const PrintStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statPrint_);
  OnNodeEnter(nodeName, statement->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  statement->PrintTarget()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName, statement->GetLocation());
}

void DotLangVisitor::Visit(const ConditionalStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statConditional_);
  OnNodeEnter(nodeName, statement->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  statement->Condition()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  statement->PositiveTarget()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  statement->NegativeTarget()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName, statement->GetLocation());
}

void DotLangVisitor::Visit(const WhileLoopStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statWhileLoop_);
  OnNodeEnter(nodeName, statement->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  statement->Condition()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  statement->Body()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName, statement->GetLocation());
}

void DotLangVisitor::Visit(const BracesStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statBraces_);
  OnNodeEnter(nodeName, statement->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  statement->List()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName, statement->GetLocation());
}

/*__________ Type Modifiers __________*/

void DotLangVisitor::Visit(const IntTypeModifier* typeModifier) {
  std::string nodeName = GenerateNodeName(NodeNames::typeModInt_);
  OnNodeEnter(nodeName, typeModifier->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  OnNodeExit(nodeName, typeModifier->GetLocation());
}

void DotLangVisitor::Visit(const BooleanTypeModifier* typeModifier) {
  std::string nodeName = GenerateNodeName(NodeNames::typeModeBool_);
  OnNodeEnter(nodeName, typeModifier->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  OnNodeExit(nodeName, typeModifier->GetLocation());
}

void DotLangVisitor::Visit(const IntArrayTypeModifier* typeModifier) {
  std::string nodeName = GenerateNodeName(NodeNames::typeModIntArray_);
  OnNodeEnter(nodeName, typeModifier->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  OnNodeExit(nodeName, typeModifier->GetLocation());
}

void DotLangVisitor::Visit(const IdTypeModifier* typeModifier) {
  std::string nodeName = GenerateNodeName(NodeNames::typeModeId_);
  OnNodeEnter(nodeName, typeModifier->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  typeModifier->TypeId()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName, typeModifier->GetLocation());
}

/*__________ Other (except lists) __________*/

void DotLangVisitor::Visit(const VarDeclaration* declaration) {
  std::string nodeName = GenerateNodeName(NodeNames::varDecl_);
  OnNodeEnter(nodeName, declaration->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  declaration->Type()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  declaration->Id()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName, declaration->GetLocation());
}

void DotLangVisitor::Visit(const MethodArgument* argument) {
  std::string nodeName = GenerateNodeName(NodeNames::methArg_);
  OnNodeEnter(nodeName, argument->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  argument->Type()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  argument->Id()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName, argument->GetLocation());
}

void DotLangVisitor::Visit(const MethodDeclaration* declaration) {
  std::string nodeName = GenerateNodeName(NodeNames::methDecl_);
  OnNodeEnter(nodeName, declaration->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  declaration->GetAccessModifier()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  declaration->GetTypeModifier()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  declaration->MethodId()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  declaration->MethodArguments()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  declaration->VarDeclarations()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  declaration->Statements()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  declaration->ReturnExpression()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName, declaration->GetLocation());
}

void DotLangVisitor::Visit(const MainClass* mainClass) {
  std::string nodeName = GenerateNodeName(NodeNames::mainClass_);
  OnNodeEnter(nodeName, mainClass->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  mainClass->ClassName()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  mainClass->ClassArgsName()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  mainClass->Statements()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName, mainClass->GetLocation());
}

void DotLangVisitor::Visit(const ClassDeclaration* declaration) {
  std::string nodeName = GenerateNodeName(NodeNames::classDecl_);
  OnNodeEnter(nodeName, declaration->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  declaration->ClassName()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  declaration->VarDeclarations()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  declaration->MethodDeclarations()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  if (declaration->HasParent()) {
    declaration->ExtendsClassName()->Accept(this);

    AddEdge(nodeName, visitedNodeStack_.back());
    visitedNodeStack_.pop_back();
  }

  OnNodeExit(nodeName, declaration->GetLocation());
}

void DotLangVisitor::Visit(const Program* program) {
  std::string nodeName = GenerateNodeName(NodeNames::program_);
  OnNodeEnter(nodeName, program->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  program->GetMainClass()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  program->ClassDeclarations()->Accept(this);
  AddEdge(nodeName, visitedNodeStack_.back());
  visitedNodeStack_.pop_back();

  OnNodeExit(nodeName, program->GetLocation());
}

/*__________  Lists __________*/

void DotLangVisitor::Visit(const ExpressionList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::expList_);
  OnNodeEnter(nodeName, list->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  const std::vector<std::unique_ptr<const Expression>>& expressions =
      list->Expressions();
  for (auto it = expressions.begin(); it != expressions.end(); ++it) {
    (*it)->Accept(this);

    AddEdge(nodeName, visitedNodeStack_.back());
    visitedNodeStack_.pop_back();
  }

  OnNodeExit(nodeName, list->GetLocation());
}

void DotLangVisitor::Visit(const StatementList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::statList_);
  OnNodeEnter(nodeName, list->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  const std::vector<std::unique_ptr<const Statement>>& statements =
      list->Statements();
  // must be reversed before being used
  for (auto rit = statements.rbegin(); rit != statements.rend(); ++rit) {
    (*rit)->Accept(this);

    AddEdge(nodeName, visitedNodeStack_.back());
    visitedNodeStack_.pop_back();
  }

  OnNodeExit(nodeName, list->GetLocation());
}

void DotLangVisitor::Visit(const VarDeclarationList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::varDeclList_);
  OnNodeEnter(nodeName, list->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  const std::vector<std::unique_ptr<const VarDeclaration>>& varDeclarations =
      list->VarDeclarations();
  for (auto it = varDeclarations.begin(); it != varDeclarations.end(); ++it) {
    (*it)->Accept(this);

    AddEdge(nodeName, visitedNodeStack_.back());
    visitedNodeStack_.pop_back();
  }

  OnNodeExit(nodeName, list->GetLocation());
}

void DotLangVisitor::Visit(const MethodArgumentList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::methAgrList_);
  OnNodeEnter(nodeName, list->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  const std::vector<std::unique_ptr<const MethodArgument>>& methodArguments =
      list->MethodArguments();
  for (auto it = methodArguments.begin(); it != methodArguments.end(); ++it) {
    (*it)->Accept(this);

    AddEdge(nodeName, visitedNodeStack_.back());
    visitedNodeStack_.pop_back();
  }

  OnNodeExit(nodeName, list->GetLocation());
}

void DotLangVisitor::Visit(const MethodDeclarationList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::methDeclList_);
  OnNodeEnter(nodeName, list->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  const std::vector<std::unique_ptr<const MethodDeclaration>>&
      methodDeclarations = list->MethodDeclarations();
  for (auto it = methodDeclarations.begin(); it != methodDeclarations.end();
       ++it) {
    (*it)->Accept(this);

    AddEdge(nodeName, visitedNodeStack_.back());
    visitedNodeStack_.pop_back();
  }

  OnNodeExit(nodeName, list->GetLocation());
}

void DotLangVisitor::Visit(const ClassDeclarationList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::classDeclList_);
  OnNodeEnter(nodeName, list->GetLocation());
  visitedNodeStack_.push_back(nodeName);

  const std::vector<std::unique_ptr<const ClassDeclaration>>&
      classDeclarations = list->ClassDeclarations();
  for (auto it = classDeclarations.begin(); it != classDeclarations.end();
       ++it) {
    (*it)->Accept(this);

    AddEdge(nodeName, visitedNodeStack_.back());
    visitedNodeStack_.pop_back();
  }

  OnNodeExit(nodeName, list->GetLocation());
}

}  // namespace Ast
