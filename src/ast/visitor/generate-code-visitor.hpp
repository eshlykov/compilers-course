#pragma once

#include <iostream>  // for verbose output
#include <iterator>
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

class GenerateCodeVisitor : public Visitor {
 public:
  explicit GenerateCodeVisitor(bool verbose = false) : Visitor(verbose) {}
  // Returns code generated on the base of the AST traversed.
  std::string GetCode() const;

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
  std::stringstream sstream_;
  std::string codeMargin_;

  void IncreaseCodeMargin();
  void DecreaseCodeMargin();
};

void GenerateCodeVisitor::IncreaseCodeMargin() { codeMargin_ += "    "; }

void GenerateCodeVisitor::DecreaseCodeMargin() {
  codeMargin_.erase(codeMargin_.size() - 4);
}

std::string GenerateCodeVisitor::GetCode() const { return sstream_.str(); }

/*__________ Access Modifiers __________*/

void GenerateCodeVisitor::Visit(const PublicAccessModifier* modifier) {
  std::string nodeName = GenerateNodeName(NodeNames::accessModePublic_);
  OnNodeEnter(nodeName, modifier->GetLocation());
  sstream_ << "public ";

  OnNodeExit(nodeName, modifier->GetLocation());
}

void GenerateCodeVisitor::Visit(const PrivateAccessModifier* modifier) {
  std::string nodeName = GenerateNodeName(NodeNames::accessModPrivate_);
  OnNodeEnter(nodeName, modifier->GetLocation());
  sstream_ << "private ";

  OnNodeExit(nodeName, modifier->GetLocation());
}

/*__________ Expressions __________*/

void GenerateCodeVisitor::Visit(const BinaryExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expBinary_);
  OnNodeEnter(nodeName, expression->GetLocation());

  expression->LeftOperand()->Accept(this);
  sstream_ << ' ' << OperatorChar(expression->Operation()) << ' ';
  expression->RightOperand()->Accept(this);

  OnNodeExit(nodeName, expression->GetLocation());
}

void GenerateCodeVisitor::Visit(const BracketExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expBracket_);
  OnNodeEnter(nodeName, expression->GetLocation());

  expression->ContainerExpression()->Accept(this);
  sstream_ << '[';
  expression->IndexExpression()->Accept(this);
  sstream_ << ']';

  OnNodeExit(nodeName, expression->GetLocation());
}

void GenerateCodeVisitor::Visit(const NumberExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expNumber_);
  OnNodeEnter(nodeName, expression->GetLocation());

  sstream_ << expression->Value();

  OnNodeExit(nodeName, expression->GetLocation());
}

void GenerateCodeVisitor::Visit(const LogicExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expLogic_);
  OnNodeEnter(nodeName, expression->GetLocation());

  sstream_ << (expression->Value() ? "true" : "false");

  OnNodeExit(nodeName, expression->GetLocation());
}

void GenerateCodeVisitor::Visit(const IdExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expId_);
  OnNodeEnter(nodeName, expression->GetLocation());

  sstream_ << expression->Name();

  OnNodeExit(nodeName, expression->GetLocation());
}

void GenerateCodeVisitor::Visit(const LengthExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expLength_);
  OnNodeEnter(nodeName, expression->GetLocation());

  expression->LengthTarget()->Accept(this);
  sstream_ << ".length";

  OnNodeExit(nodeName, expression->GetLocation());
}

void GenerateCodeVisitor::Visit(const MethodExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expMethod_);
  OnNodeEnter(nodeName, expression->GetLocation());

  expression->CallerExpression()->Accept(this);
  sstream_ << '.';

  expression->MethodId()->Accept(this);
  sstream_ << '(';

  expression->Arguments()->Accept(this);
  sstream_ << ')';

  OnNodeExit(nodeName, expression->GetLocation());
}

void GenerateCodeVisitor::Visit(const ThisExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expThis_);
  OnNodeEnter(nodeName, expression->GetLocation());

  sstream_ << "this";

  OnNodeExit(nodeName, expression->GetLocation());
}

void GenerateCodeVisitor::Visit(const NewArrayExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expNewArray_);
  OnNodeEnter(nodeName, expression->GetLocation());

  sstream_ << "new int[";
  expression->LengthExpression()->Accept(this);
  sstream_ << "]";

  OnNodeExit(nodeName, expression->GetLocation());
}

void GenerateCodeVisitor::Visit(const NewIdExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expNewId_);
  OnNodeEnter(nodeName, expression->GetLocation());

  sstream_ << "new ";
  expression->TargetId()->Accept(this);
  sstream_ << "()";

  OnNodeExit(nodeName, expression->GetLocation());
}

void GenerateCodeVisitor::Visit(const NegateExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expNegate_);
  OnNodeEnter(nodeName, expression->GetLocation());

  sstream_ << "!(";
  expression->TargetExpression()->Accept(this);
  sstream_ << ')';

  OnNodeExit(nodeName, expression->GetLocation());
}

/*__________ Statements __________*/

void GenerateCodeVisitor::Visit(const AssignIdStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statAssignId_);
  OnNodeEnter(nodeName, statement->GetLocation());

  sstream_ << codeMargin_;
  statement->LeftPart()->Accept(this);
  sstream_ << " = ";
  statement->RightPart()->Accept(this);
  sstream_ << ';' << std::endl;

  OnNodeExit(nodeName, statement->GetLocation());
}

void GenerateCodeVisitor::Visit(const AssignIdWithIndexStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statAssignIdWithIndex_);
  OnNodeEnter(nodeName, statement->GetLocation());

  sstream_ << codeMargin_;
  statement->LeftPartId()->Accept(this);
  sstream_ << '[';
  statement->LeftPartIndex()->Accept(this);
  sstream_ << ']' << " = ";
  statement->RightPart()->Accept(this);
  sstream_ << ';' << std::endl;

  OnNodeExit(nodeName, statement->GetLocation());
}

void GenerateCodeVisitor::Visit(const PrintStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statPrint_);
  OnNodeEnter(nodeName, statement->GetLocation());

  sstream_ << codeMargin_ << "System.out.println(";
  statement->PrintTarget()->Accept(this);
  sstream_ << ')' << ';' << std::endl;

  OnNodeExit(nodeName, statement->GetLocation());
}

void GenerateCodeVisitor::Visit(const ConditionalStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statConditional_);
  OnNodeEnter(nodeName, statement->GetLocation());

  sstream_ << codeMargin_ << "if (";
  statement->Condition()->Accept(this);
  sstream_ << ") " << std::endl;
  IncreaseCodeMargin();
  statement->PositiveTarget()->Accept(this);
  DecreaseCodeMargin();
  sstream_ << codeMargin_ << "else " << std::endl;
  IncreaseCodeMargin();
  statement->NegativeTarget()->Accept(this);
  DecreaseCodeMargin();

  OnNodeExit(nodeName, statement->GetLocation());
}

void GenerateCodeVisitor::Visit(const WhileLoopStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statWhileLoop_);
  OnNodeEnter(nodeName, statement->GetLocation());

  sstream_ << codeMargin_ << "while (";
  statement->Condition()->Accept(this);
  sstream_ << ") " << std::endl;

  IncreaseCodeMargin();
  statement->Body()->Accept(this);
  DecreaseCodeMargin();

  OnNodeExit(nodeName, statement->GetLocation());
}

void GenerateCodeVisitor::Visit(const BracesStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statBraces_);
  OnNodeEnter(nodeName, statement->GetLocation());

  sstream_ << codeMargin_ << '{' << std::endl;
  IncreaseCodeMargin();
  statement->List()->Accept(this);
  DecreaseCodeMargin();
  sstream_ << codeMargin_ << '}' << std::endl;

  OnNodeExit(nodeName, statement->GetLocation());
}

/*__________ Type Modifiers __________*/

void GenerateCodeVisitor::Visit(const IntTypeModifier* typeModifier) {
  std::string nodeName = GenerateNodeName(NodeNames::typeModInt_);
  OnNodeEnter(nodeName, typeModifier->GetLocation());

  sstream_ << "int ";

  OnNodeExit(nodeName, typeModifier->GetLocation());
}

void GenerateCodeVisitor::Visit(const BooleanTypeModifier* typeModifier) {
  std::string nodeName = GenerateNodeName(NodeNames::typeModeBool_);
  OnNodeEnter(nodeName, typeModifier->GetLocation());

  sstream_ << "boolean ";

  OnNodeExit(nodeName, typeModifier->GetLocation());
}

void GenerateCodeVisitor::Visit(const IntArrayTypeModifier* typeModifier) {
  std::string nodeName = GenerateNodeName(NodeNames::typeModIntArray_);
  OnNodeEnter(nodeName, typeModifier->GetLocation());

  sstream_ << "int[] ";

  OnNodeExit(nodeName, typeModifier->GetLocation());
}

void GenerateCodeVisitor::Visit(const IdTypeModifier* typeModifier) {
  std::string nodeName = GenerateNodeName(NodeNames::typeModeId_);
  OnNodeEnter(nodeName, typeModifier->GetLocation());

  typeModifier->TypeId()->Accept(this);
  sstream_ << ' ';

  OnNodeExit(nodeName, typeModifier->GetLocation());
}

/*__________ Other (except lists) __________*/

void GenerateCodeVisitor::Visit(const VarDeclaration* declaration) {
  std::string nodeName = GenerateNodeName(NodeNames::varDecl_);
  OnNodeEnter(nodeName, declaration->GetLocation());

  sstream_ << codeMargin_;
  declaration->Type()->Accept(this);
  declaration->Id()->Accept(this);
  sstream_ << ';' << std::endl;

  OnNodeExit(nodeName, declaration->GetLocation());
}

void GenerateCodeVisitor::Visit(const MethodArgument* argument) {
  std::string nodeName = GenerateNodeName(NodeNames::methArg_);
  OnNodeEnter(nodeName, argument->GetLocation());

  argument->Type()->Accept(this);
  argument->Id()->Accept(this);

  OnNodeExit(nodeName, argument->GetLocation());
}

void GenerateCodeVisitor::Visit(const MethodDeclaration* declaration) {
  std::string nodeName = GenerateNodeName(NodeNames::methDecl_);
  OnNodeEnter(nodeName, declaration->GetLocation());

  sstream_ << codeMargin_;
  declaration->GetAccessModifier()->Accept(this);
  declaration->GetTypeModifier()->Accept(this);
  declaration->MethodId()->Accept(this);
  sstream_ << '(';
  declaration->MethodArguments()->Accept(this);
  sstream_ << ") {" << std::endl;
  IncreaseCodeMargin();
  declaration->VarDeclarations()->Accept(this);
  declaration->Statements()->Accept(this);
  sstream_ << codeMargin_ << "return ";
  declaration->ReturnExpression()->Accept(this);
  sstream_ << ';' << std::endl;
  DecreaseCodeMargin();
  sstream_ << codeMargin_ << '}' << std::endl;

  OnNodeExit(nodeName, declaration->GetLocation());
}

void GenerateCodeVisitor::Visit(const MainClass* mainClass) {
  std::string nodeName = GenerateNodeName(NodeNames::mainClass_);
  OnNodeEnter(nodeName, mainClass->GetLocation());

  sstream_ << codeMargin_ << "class ";
  mainClass->ClassName()->Accept(this);
  sstream_ << ' ';
  sstream_ << '{' << std::endl;
  IncreaseCodeMargin();
  sstream_ << codeMargin_ << "public static void main(String[] ";
  mainClass->ClassArgsName()->Accept(this);
  sstream_ << ") {" << std::endl;
  IncreaseCodeMargin();
  mainClass->Statements()->Accept(this);
  DecreaseCodeMargin();
  sstream_ << codeMargin_ << '}' << std::endl;
  DecreaseCodeMargin();
  sstream_ << codeMargin_ << '}' << std::endl;

  OnNodeExit(nodeName, mainClass->GetLocation());
}

void GenerateCodeVisitor::Visit(const ClassDeclaration* declaration) {
  std::string nodeName = GenerateNodeName(NodeNames::classDecl_);
  OnNodeEnter(nodeName, declaration->GetLocation());

  sstream_ << codeMargin_ << "class ";
  declaration->ClassName()->Accept(this);
  sstream_ << ' ';
  if (declaration->HasParent()) {
    sstream_ << "extends ";
    declaration->ExtendsClassName()->Accept(this);
  }
  sstream_ << '{' << std::endl;
  IncreaseCodeMargin();

  declaration->VarDeclarations()->Accept(this);
  declaration->MethodDeclarations()->Accept(this);

  DecreaseCodeMargin();
  sstream_ << codeMargin_ << '}' << std::endl;

  OnNodeExit(nodeName, declaration->GetLocation());
}

void GenerateCodeVisitor::Visit(const Program* program) {
  std::string nodeName = GenerateNodeName(NodeNames::program_);
  OnNodeEnter(nodeName, program->GetLocation());

  program->GetMainClass()->Accept(this);
  sstream_ << std::endl;
  program->ClassDeclarations()->Accept(this);

  OnNodeExit(nodeName, program->GetLocation());
}

/*__________  Lists __________*/

void GenerateCodeVisitor::Visit(const ExpressionList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::expList_);
  OnNodeEnter(nodeName, list->GetLocation());

  const std::vector<std::unique_ptr<const Expression> >& expressions =
      list->Expressions();
  auto itLast = std::prev(expressions.end());
  for (auto it = expressions.begin(); it != expressions.end(); ++it) {
    (*it)->Accept(this);
    if (it != itLast) {
      sstream_ << ", ";
    }
  }

  OnNodeExit(nodeName, list->GetLocation());
}

void GenerateCodeVisitor::Visit(const StatementList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::statList_);
  OnNodeEnter(nodeName, list->GetLocation());

  const std::vector<std::unique_ptr<const Statement> >& statements =
      list->Statements();
  // must be reversed before being used
  for (auto rit = statements.rbegin(); rit != statements.rend(); ++rit) {
    (*rit)->Accept(this);
  }

  OnNodeExit(nodeName, list->GetLocation());
}

void GenerateCodeVisitor::Visit(const VarDeclarationList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::varDeclList_);
  OnNodeEnter(nodeName, list->GetLocation());

  const std::vector<std::unique_ptr<const VarDeclaration> >& varDeclarations =
      list->VarDeclarations();
  for (auto it = varDeclarations.begin(); it != varDeclarations.end(); ++it) {
    (*it)->Accept(this);
  }

  OnNodeExit(nodeName, list->GetLocation());
}

void GenerateCodeVisitor::Visit(const MethodArgumentList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::methAgrList_);
  OnNodeEnter(nodeName, list->GetLocation());

  const std::vector<std::unique_ptr<const MethodArgument> >& methodArguments =
      list->MethodArguments();
  auto itLast = std::prev(methodArguments.end());
  for (auto it = methodArguments.begin(); it != methodArguments.end(); ++it) {
    (*it)->Accept(this);
    if (it != itLast) {
      sstream_ << ", ";
    }
  }

  OnNodeExit(nodeName, list->GetLocation());
}

void GenerateCodeVisitor::Visit(const MethodDeclarationList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::methDeclList_);
  OnNodeEnter(nodeName, list->GetLocation());

  const std::vector<std::unique_ptr<const MethodDeclaration> >&
      methodDeclarations = list->MethodDeclarations();
  for (auto it = methodDeclarations.begin(); it != methodDeclarations.end();
       ++it) {
    (*it)->Accept(this);
    sstream_ << std::endl;
  }

  OnNodeExit(nodeName, list->GetLocation());
}

void GenerateCodeVisitor::Visit(const ClassDeclarationList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::classDeclList_);
  OnNodeEnter(nodeName, list->GetLocation());

  const std::vector<std::unique_ptr<const ClassDeclaration> >&
      classDeclarations = list->ClassDeclarations();
  for (auto it = classDeclarations.begin(); it != classDeclarations.end();
       ++it) {
    (*it)->Accept(this);
  }

  OnNodeExit(nodeName, list->GetLocation());
}

}  // namespace Ast
