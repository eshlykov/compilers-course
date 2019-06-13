#pragma once

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
#include <ast/visitor/symbol-table.hpp>
#include <utils/compilation-error.hpp>

namespace Ast {

class TypeCheckerVisitor : public Visitor {
 public:
  explicit TypeCheckerVisitor(const SymbolTable* symbolTablePtr,
                              bool verbose = false)
      : Visitor(verbose),
        symbolTablePtr_(symbolTablePtr),
        lastType_({TypeIdentifier(TypeIdentifieres::NotFound)}),
        errors_(new std::vector<CompilationError>()) {}

  const std::vector<CompilationError>* GetErrors() const;

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
  const SymbolTable* symbolTablePtr_;

  std::vector<TypeIdentifier> lastType_;
  std::shared_ptr<const ClassDefinition> lastClass_;
  std::shared_ptr<const MethodDefinition> lastMethod_;
  std::string lastId_;

  std::vector<CompilationError>* errors_;
};

const std::vector<CompilationError>* TypeCheckerVisitor::GetErrors() const {
  return errors_;
}

/*__________ Access Modifiers __________*/

// ignored
void TypeCheckerVisitor::Visit(const PublicAccessModifier* modifier) {
  std::string nodeName = GenerateNodeName(NodeNames::accessModePublic_);
  OnNodeEnter(nodeName, modifier->GetLocation());
  OnNodeExit(nodeName, modifier->GetLocation());
}

// ignored
void TypeCheckerVisitor::Visit(const PrivateAccessModifier* modifier) {
  std::string nodeName = GenerateNodeName(NodeNames::accessModPrivate_);
  OnNodeEnter(nodeName, modifier->GetLocation());
  OnNodeExit(nodeName, modifier->GetLocation());
}

/*__________ Expressions __________*/

void TypeCheckerVisitor::Visit(const BinaryExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expBinary_);
  OnNodeEnter(nodeName, expression->GetLocation());

  TypeIdentifieres operatorType;
  if (expression->Operation() == OperatorTypes::Less ||
      expression->Operation() == OperatorTypes::And ||
      expression->Operation() == OperatorTypes::Or) {
    operatorType = TypeIdentifieres::Boolean;
  } else {
    operatorType = TypeIdentifieres::Int;
  }
  expression->LeftOperand()->Accept(this);
  TypeIdentifieres leftOperandType = lastType_.front().Type();

  expression->RightOperand()->Accept(this);
  TypeIdentifieres rightOperandType = lastType_.front().Type();

  if (leftOperandType != rightOperandType) {
    errors_->push_back(
        CompilationError((expression)->GetLocation(),
                         CompilationError::differentTypesOfArguments_));
    lastType_ = {TypeIdentifier(TypeIdentifieres::NotFound)};
  } else {
    lastType_ = {TypeIdentifier(operatorType)};
  }
  OnNodeExit(nodeName, expression->GetLocation());
}

void TypeCheckerVisitor::Visit(const BracketExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expBracket_);
  OnNodeEnter(nodeName, expression->GetLocation());

  expression->ContainerExpression()->Accept(this);

  TypeIdentifieres containerType;
  if (lastType_.front().Type() == TypeIdentifieres::IntArray) {
    containerType = TypeIdentifieres::Int;
  } else {
    containerType = TypeIdentifieres::NotFound;
  }

  expression->IndexExpression()->Accept(this);

  if (lastType_.front().Type() != TypeIdentifieres::Int) {
    errors_->push_back(CompilationError((expression)->GetLocation(),
                                        CompilationError::invalidIndexType_));
  }

  lastType_ = {TypeIdentifier(containerType)};

  OnNodeExit(nodeName, expression->GetLocation());
}

void TypeCheckerVisitor::Visit(const NumberExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expNumber_);
  OnNodeEnter(nodeName, expression->GetLocation());

  lastType_ = {TypeIdentifier(TypeIdentifieres::Int)};

  OnNodeExit(nodeName, expression->GetLocation());
}

void TypeCheckerVisitor::Visit(const LogicExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expLogic_);
  OnNodeEnter(nodeName, expression->GetLocation());

  lastType_ = {TypeIdentifier(TypeIdentifieres::Boolean)};

  OnNodeExit(nodeName, expression->GetLocation());
}

void TypeCheckerVisitor::Visit(const IdExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expId_);
  OnNodeEnter(nodeName, expression->GetLocation());

  std::string name = expression->Name();
  TypeIdentifier notFound(TypeIdentifieres::NotFound);

  TypeIdentifier fieldLurk =
      symbolTablePtr_->SearchClassHierarchyForField(name, lastClass_);
  // TODO: do we really have to perform methodLurk?
  std::shared_ptr<const MethodDefinition> methodLurk =
      symbolTablePtr_->SearchClassHierarchyForMethod(name, lastClass_);
  TypeIdentifier localLurk = lastMethod_->GetLocalVariableType(name);
  TypeIdentifier argumentLurk = lastMethod_->GetArgumentType(name);

  lastType_ = {TypeIdentifier(TypeIdentifieres::NotFound)};

  // The latter wins.
  if (fieldLurk != notFound) {
    lastType_ = {fieldLurk};
  }
  if (methodLurk != nullptr && methodLurk->ReturnType() != notFound) {
    lastType_ = {methodLurk->ReturnType()};
  }
  if (argumentLurk != notFound) {
    lastType_ = {argumentLurk};
  }
  if (localLurk != notFound) {
    lastType_ = {localLurk};
  }

  if (lastType_.front().Type() == TypeIdentifieres::NotFound) {
    errors_->push_back(CompilationError(expression->GetLocation(),
                                        CompilationError::undefinedVar_));
  }

  OnNodeExit(nodeName, expression->GetLocation());
}

void TypeCheckerVisitor::Visit(const LengthExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expLength_);
  OnNodeEnter(nodeName, expression->GetLocation());

  expression->LengthTarget()->Accept(this);
  lastType_ = {TypeIdentifier(TypeIdentifieres::Int)};

  OnNodeExit(nodeName, expression->GetLocation());
}

void TypeCheckerVisitor::Visit(const MethodExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expMethod_);
  OnNodeEnter(nodeName, expression->GetLocation());

  TypeIdentifier methodReturnType = TypeIdentifier(TypeIdentifieres::NotFound);
  expression->CallerExpression()->Accept(this);

  std::string methodName = expression->MethodId()->Name();
  std::string className = lastType_.front().ClassName();

  std::shared_ptr<const ClassDefinition> callerClassDefinition;

  callerClassDefinition = symbolTablePtr_->GetClassDefinition(className);

  if (callerClassDefinition == nullptr) {
    errors_->emplace_back(expression->GetLocation(),
                          CompilationError::invalidCallerExpression_);
  } else {
    std::shared_ptr<const MethodDefinition> methodDefinition =
        symbolTablePtr_->SearchClassHierarchyForMethod(methodName,
                                                       callerClassDefinition);

    if (methodDefinition == nullptr) {
      errors_->emplace_back(expression->GetLocation(),
                            CompilationError::classHasNoMethod_);
      methodReturnType = TypeIdentifier(TypeIdentifieres::NotFound);
    } else {
      if (methodDefinition->AccessModifier() == AccessModifiers::Private &&
          callerClassDefinition != lastClass_) {
        errors_->emplace_back(expression->GetLocation(),
                              CompilationError::methodIsPrivate_);
      }

      expression->Arguments()->Accept(this);
      if (lastType_.size() != methodDefinition->GetArgumentsNumber()) {
        errors_->emplace_back(expression->GetLocation(),
                              CompilationError::argCountsNotMatch_);
      } else {
        for (int i = 0; i < lastType_.size(); ++i) {
          TypeIdentifier expectedType = methodDefinition->GetArgumentType(i);
          if (lastType_[i] != expectedType) {
            bool canBeResolved = false;
            if (lastType_[i].Type() == TypeIdentifieres::ClassId &&
                expectedType.Type() == TypeIdentifieres::ClassId) {
              std::shared_ptr<const ClassDefinition> ancestor =
                  symbolTablePtr_->GetClassDefinition(lastType_[i].ClassName());
              while (ancestor != nullptr) {
                if (ancestor->ClassName() == expectedType.ClassName()) {
                  canBeResolved = true;
                  break;
                }
                if (ancestor->HasParent()) {
                  ancestor = symbolTablePtr_->GetClassDefinition(
                      ancestor->GetParentName());
                } else {
                  ancestor = nullptr;
                }
              }
            }
            if (!canBeResolved) {
              errors_->emplace_back(expression->GetLocation(),
                                    CompilationError::argTypesNotMatch_);
            }
          }
        }
      }
      methodReturnType = methodDefinition->ReturnType();
    }
  }

  lastType_ = {methodReturnType};

  OnNodeExit(nodeName, expression->GetLocation());
}

// ignored
void TypeCheckerVisitor::Visit(const ThisExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expThis_);
  OnNodeEnter(nodeName, expression->GetLocation());

  lastType_ = {TypeIdentifier(lastClass_->ClassName())};

  OnNodeExit(nodeName, expression->GetLocation());
}

void TypeCheckerVisitor::Visit(const NewArrayExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expNewArray_);
  OnNodeEnter(nodeName, expression->GetLocation());

  expression->LengthExpression()->Accept(this);

  if (lastType_.front().Type() != TypeIdentifieres::Int) {
    lastType_ = {TypeIdentifier(TypeIdentifieres::NotFound)};
    errors_->push_back(CompilationError(expression->GetLocation(),
                                        CompilationError::invalidLengthType_));
  } else {
    lastType_ = {TypeIdentifier(TypeIdentifieres::IntArray)};
  }

  lastType_ = {TypeIdentifier(TypeIdentifieres::IntArray)};

  OnNodeExit(nodeName, expression->GetLocation());
}

void TypeCheckerVisitor::Visit(const NewIdExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expNewId_);
  OnNodeEnter(nodeName, expression->GetLocation());

  std::string className = expression->TargetId()->Name();

  if (symbolTablePtr_->GetClassDefinition(className) == nullptr) {
    errors_->push_back(CompilationError(expression->GetLocation(),
                                        CompilationError::typeNotExists_));
  }

  lastType_ = {TypeIdentifier(className)};

  OnNodeExit(nodeName, expression->GetLocation());
}

void TypeCheckerVisitor::Visit(const NegateExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expNegate_);
  OnNodeEnter(nodeName, expression->GetLocation());

  expression->TargetExpression()->Accept(this);
  // It should stay intact.
  lastType_ = {TypeIdentifier(TypeIdentifieres::Boolean)};

  OnNodeExit(nodeName, expression->GetLocation());
}

/*__________ Statements __________*/

void TypeCheckerVisitor::Visit(const AssignIdStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statAssignId_);
  OnNodeEnter(nodeName, statement->GetLocation());

  statement->LeftPart()->Accept(this);
  TypeIdentifieres leftPartLocalType = lastType_.front().Type();

  statement->RightPart()->Accept(this);
  TypeIdentifieres rightPartLocalType = lastType_.front().Type();

  if (leftPartLocalType != rightPartLocalType) {
    errors_->push_back(
        CompilationError((statement->LeftPart())->GetLocation(),
                         CompilationError::differentTypesOfArguments_));
  }
  lastType_ = {TypeIdentifier(TypeIdentifieres::NotFound)};

  OnNodeExit(nodeName, statement->GetLocation());
}

void TypeCheckerVisitor::Visit(const AssignIdWithIndexStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statAssignIdWithIndex_);
  OnNodeEnter(nodeName, statement->GetLocation());

  statement->RightPart()->Accept(this);
  TypeIdentifieres rightOperandType = lastType_.front().Type();
  statement->LeftPartIndex()->Accept(this);
  TypeIdentifieres leftOperandType = lastType_.front().Type();
  if (leftOperandType != TypeIdentifieres::Int) {
    errors_->push_back(
        CompilationError((statement->LeftPartId())->GetLocation(),
                         CompilationError::invalidIndexType_));
  }
  if (rightOperandType != TypeIdentifieres::Int) {
    errors_->push_back(
        CompilationError((statement->RightPart())->GetLocation(),
                         CompilationError::differentTypesOfArguments_));
  }

  lastType_ = {TypeIdentifier(TypeIdentifieres::NotFound)};

  OnNodeExit(nodeName, statement->GetLocation());
}

void TypeCheckerVisitor::Visit(const PrintStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statPrint_);
  OnNodeEnter(nodeName, statement->GetLocation());

  statement->PrintTarget()->Accept(this);

  if (lastType_.front().Type() != TypeIdentifieres::Int) {
    errors_->push_back(CompilationError((statement)->GetLocation(),
                                        CompilationError::invalidPrintType_));
  }
  lastType_ = {TypeIdentifier(TypeIdentifieres::NotFound)};

  OnNodeExit(nodeName, statement->GetLocation());
}

void TypeCheckerVisitor::Visit(const ConditionalStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statConditional_);
  OnNodeEnter(nodeName, statement->GetLocation());

  statement->Condition()->Accept(this);
  if (lastType_.front().Type() != TypeIdentifieres::Boolean) {
    errors_->push_back(CompilationError(
        (statement)->GetLocation(), CompilationError::invalidConditionType_));
  }
  statement->PositiveTarget()->Accept(this);
  statement->NegativeTarget()->Accept(this);
  lastType_ = {TypeIdentifier(TypeIdentifieres::NotFound)};

  OnNodeExit(nodeName, statement->GetLocation());
}

void TypeCheckerVisitor::Visit(const WhileLoopStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statWhileLoop_);
  OnNodeEnter(nodeName, statement->GetLocation());

  statement->Condition()->Accept(this);
  if (lastType_.front().Type() != TypeIdentifieres::Boolean) {
    errors_->push_back(CompilationError(
        (statement)->GetLocation(), CompilationError::invalidConditionType_));
  }
  statement->Body()->Accept(this);
  lastType_ = {TypeIdentifier(TypeIdentifieres::NotFound)};

  OnNodeExit(nodeName, statement->GetLocation());
}

void TypeCheckerVisitor::Visit(const BracesStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statBraces_);
  OnNodeEnter(nodeName, statement->GetLocation());

  statement->List()->Accept(this);
  lastType_ = {TypeIdentifier(TypeIdentifieres::NotFound)};

  OnNodeExit(nodeName, statement->GetLocation());
}

/*__________ Type Modifiers __________*/

// ignored
void TypeCheckerVisitor::Visit(const IntTypeModifier* typeModifier) {
  std::string nodeName = GenerateNodeName(NodeNames::typeModInt_);
  OnNodeEnter(nodeName, typeModifier->GetLocation());
  OnNodeExit(nodeName, typeModifier->GetLocation());
}

// ignored
void TypeCheckerVisitor::Visit(const BooleanTypeModifier* typeModifier) {
  std::string nodeName = GenerateNodeName(NodeNames::typeModeBool_);
  OnNodeEnter(nodeName, typeModifier->GetLocation());
  OnNodeExit(nodeName, typeModifier->GetLocation());
}

// ignored
void TypeCheckerVisitor::Visit(const IntArrayTypeModifier* typeModifier) {
  std::string nodeName = GenerateNodeName(NodeNames::typeModIntArray_);
  OnNodeEnter(nodeName, typeModifier->GetLocation());
  OnNodeExit(nodeName, typeModifier->GetLocation());
}

void TypeCheckerVisitor::Visit(const IdTypeModifier* typeModifier) {
  std::string nodeName = GenerateNodeName(NodeNames::typeModeId_);
  OnNodeEnter(nodeName, typeModifier->GetLocation());

  std::string className = typeModifier->TypeId()->Name();

  if (symbolTablePtr_->GetClassDefinition(className) == nullptr) {
    errors_->push_back(CompilationError(typeModifier->GetLocation(),
                                        CompilationError::typeNotExists_));
  }

  lastType_ = {TypeIdentifier(className)};

  OnNodeExit(nodeName, typeModifier->GetLocation());
}

/*__________ Other (except lists) __________*/

void TypeCheckerVisitor::Visit(const VarDeclaration* declaration) {
  std::string nodeName = GenerateNodeName(NodeNames::varDecl_);
  OnNodeEnter(nodeName, declaration->GetLocation());

  declaration->Type()->Accept(this);
  lastType_ = {TypeIdentifier(TypeIdentifieres::NotFound)};

  OnNodeExit(nodeName, declaration->GetLocation());
}

void TypeCheckerVisitor::Visit(const MethodArgument* argument) {
  std::string nodeName = GenerateNodeName(NodeNames::methArg_);
  OnNodeEnter(nodeName, argument->GetLocation());

  argument->Type()->Accept(this);
  // Let lastType fall through.

  OnNodeExit(nodeName, argument->GetLocation());
}

void TypeCheckerVisitor::Visit(const MethodDeclaration* declaration) {
  std::string nodeName = GenerateNodeName(NodeNames::methDecl_);
  OnNodeEnter(nodeName, declaration->GetLocation());

  std::string name = declaration->MethodId()->Name();
  lastMethod_ = lastClass_->GetMethodDefinition(name);

  declaration->GetTypeModifier()->Accept(this);
  declaration->MethodArguments()->Accept(this);
  declaration->VarDeclarations()->Accept(this);
  declaration->Statements()->Accept(this);
  declaration->ReturnExpression()->Accept(this);

  lastMethod_ = nullptr;
  lastType_ = {TypeIdentifier(TypeIdentifieres::NotFound)};

  OnNodeExit(nodeName, declaration->GetLocation());
}

void TypeCheckerVisitor::Visit(const MainClass* mainClass) {
  std::string nodeName = GenerateNodeName(NodeNames::mainClass_);
  OnNodeEnter(nodeName, mainClass->GetLocation());

  mainClass->Statements()->Accept(this);
  lastType_ = {TypeIdentifier(TypeIdentifieres::NotFound)};

  OnNodeExit(nodeName, mainClass->GetLocation());
}

void TypeCheckerVisitor::Visit(const ClassDeclaration* declaration) {
  std::string nodeName = GenerateNodeName(NodeNames::classDecl_);
  OnNodeEnter(nodeName, declaration->GetLocation());

  using ClassDefinitionPtr = std::shared_ptr<const ClassDefinition>;

  std::string thisClassName = declaration->ClassName()->Name();
  lastClass_ = symbolTablePtr_->GetClassDefinition(thisClassName);

  declaration->VarDeclarations()->Accept(this);
  declaration->MethodDeclarations()->Accept(this);

  if (declaration->HasParent()) {
    std::string parentName = declaration->ExtendsClassName()->Name();
    ClassDefinitionPtr parentClassDefinition =
        symbolTablePtr_->GetClassDefinition(parentName);

    if (parentClassDefinition == nullptr) {
      errors_->push_back(CompilationError(
          declaration->GetLocation(), CompilationError::parentClassNotExists_));
    } else {
      while (parentClassDefinition != nullptr &&
             parentClassDefinition->HasParent() &&
             parentClassDefinition->ClassName() != thisClassName) {
        parentName = parentClassDefinition->GetParentName();
        parentClassDefinition = symbolTablePtr_->GetClassDefinition(parentName);
      }

      if (parentName == thisClassName) {
        errors_->push_back(CompilationError(
            declaration->GetLocation(), CompilationError::cyclicInheritance_));
      }
    }
  }

  lastClass_ = nullptr;
  lastType_ = {TypeIdentifier(TypeIdentifieres::NotFound)};

  OnNodeExit(nodeName, declaration->GetLocation());
}

void TypeCheckerVisitor::Visit(const Program* program) {
  std::string nodeName = GenerateNodeName(NodeNames::program_);
  OnNodeEnter(nodeName, program->GetLocation());

  program->GetMainClass()->Accept(this);
  program->ClassDeclarations()->Accept(this);
  lastType_ = {TypeIdentifier(TypeIdentifieres::NotFound)};

  OnNodeExit(nodeName, program->GetLocation());
}

/*__________  Lists __________*/

void TypeCheckerVisitor::Visit(const ExpressionList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::expList_);
  OnNodeEnter(nodeName, list->GetLocation());

  std::vector<TypeIdentifier> types;

  const std::vector<std::unique_ptr<const Expression> >& expressions =
      list->Expressions();
  for (auto it = expressions.begin(); it != expressions.end(); ++it) {
    (*it)->Accept(this);
    types.push_back(lastType_.front());
  }

  lastType_ = types;

  OnNodeExit(nodeName, list->GetLocation());
}

void TypeCheckerVisitor::Visit(const StatementList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::statList_);
  OnNodeEnter(nodeName, list->GetLocation());

  const std::vector<std::unique_ptr<const Statement> >& statements =
      list->Statements();
  for (auto it = statements.rbegin(); it != statements.rend(); ++it) {
    (*it)->Accept(this);
  }
  lastType_ = {TypeIdentifier(TypeIdentifieres::NotFound)};

  OnNodeExit(nodeName, list->GetLocation());
}

void TypeCheckerVisitor::Visit(const VarDeclarationList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::varDeclList_);
  OnNodeEnter(nodeName, list->GetLocation());

  const std::vector<std::unique_ptr<const VarDeclaration> >& varDeclarations =
      list->VarDeclarations();
  for (auto it = varDeclarations.begin(); it != varDeclarations.end(); ++it) {
    (*it)->Accept(this);
  }
  lastType_ = {TypeIdentifier(TypeIdentifieres::NotFound)};

  OnNodeExit(nodeName, list->GetLocation());
}

void TypeCheckerVisitor::Visit(const MethodArgumentList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::methAgrList_);
  OnNodeEnter(nodeName, list->GetLocation());

  const std::vector<std::unique_ptr<const MethodArgument> >& methodArguments =
      list->MethodArguments();
  for (auto it = methodArguments.begin(); it != methodArguments.end(); ++it) {
    (*it)->Accept(this);
  }
  lastType_ = {TypeIdentifier(TypeIdentifieres::NotFound)};

  OnNodeExit(nodeName, list->GetLocation());
}

void TypeCheckerVisitor::Visit(const MethodDeclarationList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::methDeclList_);
  OnNodeEnter(nodeName, list->GetLocation());

  const std::vector<std::unique_ptr<const MethodDeclaration> >&
      methodDeclarations = list->MethodDeclarations();
  for (auto it = methodDeclarations.begin(); it != methodDeclarations.end();
       ++it) {
    (*it)->Accept(this);
  }
  lastType_ = {TypeIdentifier(TypeIdentifieres::NotFound)};

  OnNodeExit(nodeName, list->GetLocation());
}

void TypeCheckerVisitor::Visit(const ClassDeclarationList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::classDeclList_);
  OnNodeEnter(nodeName, list->GetLocation());

  const std::vector<std::unique_ptr<const ClassDeclaration> >&
      classDeclarations = list->ClassDeclarations();
  for (auto it = classDeclarations.begin(); it != classDeclarations.end();
       ++it) {
    (*it)->Accept(this);
  }
  lastType_ = {TypeIdentifier(TypeIdentifieres::NotFound)};

  OnNodeExit(nodeName, list->GetLocation());
}

}  // namespace Ast
