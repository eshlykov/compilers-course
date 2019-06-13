#pragma once

#include <unordered_map>
#include <unordered_set>
#include <utility>

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

#include <irt/node/expression-list.hpp>
#include <irt/node/expression.hpp>
#include <irt/node/statement.hpp>

#include <irt/wrapper/subtree-wrapper.hpp>

#include <irt/frame/frame.hpp>

#include <ast/visitor/symbol-table.hpp>

namespace Ast {

using MethodToIrtMap =
    std::unordered_map<std::string, std::unique_ptr<const Irt::Statement>>;

class IrtBuilderVisitor : public Visitor {
 public:
  explicit IrtBuilderVisitor(const SymbolTable* table, bool verbose = false)
      : Visitor(verbose),
        symbolTable_(table),
        methodTrees_(new MethodToIrtMap()) {}

  std::unique_ptr<const MethodToIrtMap> MethodTrees();

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
  Irt::OperatorTypes OperatorFromAstToIr(OperatorTypes type) const;
  void UpdateSubtreeWrapper(Irt::ISubtreeWrapper* wrapperNew);
  void UpdateSubtreeWrapper(std::unique_ptr<Irt::ISubtreeWrapper> wrapperNew);
  std::string MakeMethodFullName(const std::string& className,
                                 const std::string& methodName);

  template <class InputIteratorArguments, class InputIteratorLocals,
            class InputIteratorFields>
  void BuildNewFrame(const std::string& className,
                     const std::string& methodName,
                     InputIteratorArguments argumentsLeftIt,
                     InputIteratorArguments argumentsRightIt,
                     InputIteratorLocals localsLeftIt,
                     InputIteratorLocals localsRightIt,
                     InputIteratorFields fieldsLeftIt,
                     InputIteratorFields fieldsRightIt);
  void BuildNewFrame(const MethodDeclaration* declaration);
  void BuildNewFrame(const MainClass* mainClass);

  std::unique_ptr<Irt::ISubtreeWrapper> subtreeWrapper_;

  const SymbolTable* symbolTable_;

  // frame
  std::string classCurrentName_;
  std::unordered_map<std::string, std::unique_ptr<const Irt::Frame>> frames_;
  Irt::Frame* frameCurrent_;

  // used when translating expr.methodName() to determine the name of the class
  // of expr
  std::string methodCallerClassName_;

  // result
  std::unique_ptr<MethodToIrtMap> methodTrees_;
};

using MethodToIrtMap =
    std::unordered_map<std::string, std::unique_ptr<const Irt::Statement>>;

std::unique_ptr<const MethodToIrtMap> IrtBuilderVisitor::MethodTrees() {
  return std::unique_ptr<const MethodToIrtMap>(methodTrees_.release());
}

Irt::OperatorTypes IrtBuilderVisitor::OperatorFromAstToIr(
    OperatorTypes type) const {
  Irt::OperatorTypes typeResult;
  switch (type) {
    case OperatorTypes::Plus:
      typeResult = Irt::OperatorTypes::Plus;
      break;
    case OperatorTypes::Minus:
      typeResult = Irt::OperatorTypes::Minus;
      break;
    case OperatorTypes::Times:
      typeResult = Irt::OperatorTypes::Times;
      break;
    case OperatorTypes::Div:
      typeResult = Irt::OperatorTypes::Div;
      break;
    case OperatorTypes::Mod:
      typeResult = Irt::OperatorTypes::Mod;
      break;
    case OperatorTypes::And:
      typeResult = Irt::OperatorTypes::And;
      break;
    case OperatorTypes::Or:
      typeResult = Irt::OperatorTypes::Or;
      break;
    default: {
      // such cases should never happen
      assert(false);
    }
  }
  return typeResult;
}

void IrtBuilderVisitor::UpdateSubtreeWrapper(Irt::ISubtreeWrapper* wrapperNew) {
  subtreeWrapper_ = std::unique_ptr<Irt::ISubtreeWrapper>(wrapperNew);
}

void IrtBuilderVisitor::UpdateSubtreeWrapper(
    std::unique_ptr<Irt::ISubtreeWrapper> wrapperNew) {
  subtreeWrapper_ = std::move(wrapperNew);
}

std::string IrtBuilderVisitor::MakeMethodFullName(
    const std::string& className, const std::string& methodName) {
  return className + "@" + methodName;
}

template <class InputIteratorArguments, class InputIteratorLocals,
          class InputIteratorFields>
void IrtBuilderVisitor::BuildNewFrame(const std::string& className,
                                      const std::string& methodName,
                                      InputIteratorArguments argumentsLeftIt,
                                      InputIteratorArguments argumentsRightIt,
                                      InputIteratorLocals localsLeftIt,
                                      InputIteratorLocals localsRightIt,
                                      InputIteratorFields fieldsLeftIt,
                                      InputIteratorFields fieldsRightIt) {
  std::unique_ptr<Irt::Frame> frameNew =
      std::unique_ptr<Irt::Frame>(new Irt::Frame(className, methodName));

  frameCurrent_ = frameNew.get();

  frameCurrent_->AddThisAddress();
  for (auto it = fieldsLeftIt; it != fieldsRightIt; ++it) {
    frameCurrent_->AddFieldAddress(*it);
  }
  // arguments and locals should be added after fields
  // in order to overwrite them in the map of addresses in case of name
  // collision
  for (auto it = argumentsLeftIt; it != argumentsRightIt; ++it) {
    frameCurrent_->AddArgumentAddress(*it);
  }
  frameCurrent_->AddReturnAddress();
  for (auto it = localsLeftIt; it != localsRightIt; ++it) {
    frameCurrent_->AddLocalAddress(*it);
  }

  std::string methodFullName = MakeMethodFullName(className, methodName);
  frames_.emplace(methodFullName, std::move(frameNew));
}

void IrtBuilderVisitor::BuildNewFrame(const MethodDeclaration* declaration) {
  std::shared_ptr<const ClassDefinition> classDefinition =
      symbolTable_->GetClassDefinition(classCurrentName_);
  std::shared_ptr<const MethodDefinition> methodDefinition =
      classDefinition->GetMethodDefinition(declaration->MethodId()->Name());

  const std::vector<std::unique_ptr<const MethodArgument>>& arguments =
      declaration->MethodArguments()->MethodArguments();
  std::vector<std::string> argumentsNames;
  argumentsNames.reserve(arguments.size());
  for (auto it = arguments.begin(); it != arguments.end(); ++it) {
    argumentsNames.push_back((*it)->Id()->Name());
  }

  auto locals = methodDefinition->LocalVariables();
  std::vector<std::string> localsNames;
  localsNames.reserve(locals->size());
  for (auto it = locals->begin(); it != locals->end(); ++it) {
    localsNames.push_back(it->first);
  }

  std::unordered_set<std::string> fieldsNames;
  std::shared_ptr<const ClassDefinition> baseClass = classDefinition;
  while (baseClass) {
    auto fields = baseClass->Fields();
    for (auto it = fields.begin(); it != fields.end(); ++it) {
      fieldsNames.insert(it->first);
    }
    baseClass =
        baseClass->HasParent()
            ? symbolTable_->GetClassDefinition(baseClass->GetParentName())
            : nullptr;
  }

  BuildNewFrame(classCurrentName_, declaration->MethodId()->Name(),
                argumentsNames.begin(), argumentsNames.end(),
                localsNames.begin(), localsNames.end(), fieldsNames.begin(),
                fieldsNames.end());
}

void IrtBuilderVisitor::BuildNewFrame(const MainClass* mainClass) {
  std::unordered_set<std::string> emptySet;
  BuildNewFrame(mainClass->ClassName()->Name(), "main", emptySet.end(),
                emptySet.end(), emptySet.end(), emptySet.end(), emptySet.end(),
                emptySet.end());
}

/*__________ Access Modifiers __________*/

void IrtBuilderVisitor::Visit(const PublicAccessModifier* modifier) {
  std::string nodeName = GenerateNodeName(NodeNames::accessModePublic_);
  OnNodeEnter(nodeName, modifier->GetLocation());

  // such calls should never happen
  assert(false);

  OnNodeExit(nodeName, modifier->GetLocation());
}

void IrtBuilderVisitor::Visit(const PrivateAccessModifier* modifier) {
  std::string nodeName = GenerateNodeName(NodeNames::accessModPrivate_);
  OnNodeEnter(nodeName, modifier->GetLocation());

  // such calls should never happen
  assert(false);

  OnNodeExit(nodeName, modifier->GetLocation());
}

/*__________ Expressions __________*/

void IrtBuilderVisitor::Visit(const BinaryExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expBinary_);
  OnNodeEnter(nodeName, expression->GetLocation());

  expression->LeftOperand()->Accept(this);
  std::unique_ptr<Irt::ISubtreeWrapper> wrapperLeft =
      std::move(subtreeWrapper_);

  expression->RightOperand()->Accept(this);
  std::unique_ptr<Irt::ISubtreeWrapper> wrapperRight =
      std::move(subtreeWrapper_);

  if (expression->Operation() == OperatorTypes::Less) {
    UpdateSubtreeWrapper(new Irt::RelativeConditionalWrapper(
        Irt::LogicOperatorTypes::Less, std::move(wrapperLeft->ToExpression()),
        std::move(wrapperRight->ToExpression())));
  } else if (expression->Operation() == OperatorTypes::And) {
    UpdateSubtreeWrapper(new Irt::AndConditionalWrapper(
        std::move(wrapperLeft), std::move(wrapperRight)));
  } else if (expression->Operation() == OperatorTypes::Or) {
    UpdateSubtreeWrapper(new Irt::OrConditionalWrapper(
        std::move(wrapperLeft), std::move(wrapperRight)));
  } else {
    Irt::OperatorTypes operatorType =
        OperatorFromAstToIr(expression->Operation());

    UpdateSubtreeWrapper(new Irt::ExpressionWrapper(new Irt::BinaryExpression(
        operatorType, std::move(wrapperLeft->ToExpression()),
        std::move(wrapperRight->ToExpression()))));
  }

  OnNodeExit(nodeName, expression->GetLocation());
}

void IrtBuilderVisitor::Visit(const BracketExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expBracket_);
  OnNodeEnter(nodeName, expression->GetLocation());

  expression->ContainerExpression()->Accept(this);
  std::unique_ptr<const Irt::Expression> containerExpression =
      std::move(subtreeWrapper_->ToExpression());

  expression->IndexExpression()->Accept(this);
  std::unique_ptr<const Irt::Expression> indexExpression =
      std::move(subtreeWrapper_->ToExpression());

  UpdateSubtreeWrapper(new Irt::ExpressionWrapper(
      new Irt::MemExpression(new Irt::BinaryExpression(
          Irt::OperatorTypes::Plus, std::move(containerExpression),
          std::move(
              std::unique_ptr<const Irt::Expression>(new Irt::BinaryExpression(
                  Irt::OperatorTypes::Times,
                  new Irt::BinaryExpression(
                      Irt::OperatorTypes::Plus, std::move(indexExpression),
                      std::move(std::unique_ptr<const Irt::Expression>(
                          new Irt::ConstExpression(1)))),
                  new Irt::ConstExpression(frameCurrent_->GetWordSize()))))))));

  OnNodeExit(nodeName, expression->GetLocation());
}

void IrtBuilderVisitor::Visit(const NumberExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expNumber_);
  OnNodeEnter(nodeName, expression->GetLocation());

  UpdateSubtreeWrapper(new Irt::ExpressionWrapper(
      new Irt::ConstExpression(expression->Value())));

  OnNodeExit(nodeName, expression->GetLocation());
}

void IrtBuilderVisitor::Visit(const LogicExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expLogic_);
  OnNodeEnter(nodeName, expression->GetLocation());

  UpdateSubtreeWrapper(new Irt::ExpressionWrapper(
      new Irt::ConstExpression(expression->Value() ? 1 : 0)));

  OnNodeExit(nodeName, expression->GetLocation());
}

void IrtBuilderVisitor::Visit(const IdExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expId_);
  OnNodeEnter(nodeName, expression->GetLocation());

  const Irt::IAddress* address = frameCurrent_->GetAddress(expression->Name());

  if (address != nullptr) {
    // expression is a name of local var / argument / field

    std::shared_ptr<const ClassDefinition> classDefinition =
        symbolTable_->GetClassDefinition(frameCurrent_->GetClassName());
    std::shared_ptr<const MethodDefinition> methodDefinition =
        classDefinition->GetMethodDefinition(frameCurrent_->GetMethodName());
    TypeIdentifier type = methodDefinition->GetVariableType(expression->Name());
    if (type.Type() == TypeIdentifieres::NotFound) {
      // expression is a name of field
      UpdateSubtreeWrapper(
          new Irt::ExpressionWrapper(std::move(address->ToExpression())));
      type = classDefinition->GetFieldType(expression->Name());
    } else {
      // expression is a name of local var / argument
      UpdateSubtreeWrapper(
          new Irt::ExpressionWrapper(std::move(address->ToExpression())));
    }

    if (type.Type() == TypeIdentifieres::ClassId) {
      methodCallerClassName_ = type.ClassName();
    }
  }

  OnNodeExit(nodeName, expression->GetLocation());
}

void IrtBuilderVisitor::Visit(const LengthExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expLength_);
  OnNodeEnter(nodeName, expression->GetLocation());

  expression->LengthTarget()->Accept(this);
  std::unique_ptr<const Irt::Expression> targetExpression =
      std::move(subtreeWrapper_->ToExpression());

  UpdateSubtreeWrapper(new Irt::ExpressionWrapper(std::move(targetExpression)));

  OnNodeExit(nodeName, expression->GetLocation());
}

void IrtBuilderVisitor::Visit(const MethodExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expMethod_);
  OnNodeEnter(nodeName, expression->GetLocation());

  expression->CallerExpression()->Accept(this);
  std::string methodCaller = methodCallerClassName_;

  Irt::ExpressionList* expressionListIrt = new Irt::ExpressionList();
  expressionListIrt->Add(std::move(subtreeWrapper_->ToExpression()));

  const std::vector<std::unique_ptr<const Expression>>& expressionsAst =
      expression->Arguments()->Expressions();
  for (auto it = expressionsAst.begin(); it != expressionsAst.end(); ++it) {
    (*it)->Accept(this);
    expressionListIrt->Add(std::move(subtreeWrapper_->ToExpression()));
  }

  UpdateSubtreeWrapper(new Irt::ExpressionWrapper(new Irt::CallExpression(
      new Irt::NameExpression(Address(
          MakeMethodFullName(methodCaller, expression->MethodId()->Name()))),
      expressionListIrt)));

  std::shared_ptr<const ClassDefinition> classDefinition =
      symbolTable_->GetClassDefinition(methodCaller);
  std::shared_ptr<const MethodDefinition> methodDefinition =
      symbolTable_->SearchClassHierarchyForMethod(
          expression->MethodId()->Name(), classDefinition);
  TypeIdentifier type = methodDefinition->ReturnType();
  if (type.Type() == TypeIdentifieres::ClassId) {
    methodCallerClassName_ = type.ClassName();
  }

  OnNodeExit(nodeName, expression->GetLocation());
}

void IrtBuilderVisitor::Visit(const ThisExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expThis_);
  OnNodeEnter(nodeName, expression->GetLocation());

  UpdateSubtreeWrapper(new Irt::ExpressionWrapper(
      std::move(frameCurrent_->GetThisAddress()->ToExpression())));
  methodCallerClassName_ = classCurrentName_;

  OnNodeExit(nodeName, expression->GetLocation());
}

void IrtBuilderVisitor::Visit(const NewArrayExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expNewArray_);
  OnNodeEnter(nodeName, expression->GetLocation());

  expression->LengthExpression()->Accept(this);

  std::unique_ptr<const Irt::Expression> expressionLength =
      std::move(subtreeWrapper_->ToExpression());

  UpdateSubtreeWrapper(
      new Irt::ExpressionWrapper(std::move(frameCurrent_->ExternalCall(
          "malloc",
          std::move(std::unique_ptr<const Irt::ExpressionList>(
              new Irt::ExpressionList(new Irt::BinaryExpression(
                  Irt::OperatorTypes::Times,
                  new Irt::BinaryExpression(
                      Irt::OperatorTypes::Plus, std::move(expressionLength),
                      std::move(std::unique_ptr<Irt::ConstExpression>(
                          new Irt::ConstExpression(1)))),
                  new Irt::ConstExpression(
                      frameCurrent_->GetWordSize())))))))));

  OnNodeExit(nodeName, expression->GetLocation());
}

void IrtBuilderVisitor::Visit(const NewIdExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expNewId_);
  OnNodeEnter(nodeName, expression->GetLocation());

  std::shared_ptr<const ClassDefinition> classDefinition =
      symbolTable_->GetClassDefinition(expression->TargetId()->Name());
  int fieldCount = classDefinition->Fields().size();

  UpdateSubtreeWrapper(
      new Irt::ExpressionWrapper(std::move(frameCurrent_->ExternalCall(
          "malloc", std::move(std::unique_ptr<const Irt::ExpressionList>(
                        new Irt::ExpressionList(new Irt::BinaryExpression(
                            Irt::OperatorTypes::Times,
                            new Irt::ConstExpression(fieldCount),
                            new Irt::ConstExpression(
                                frameCurrent_->GetWordSize())))))))));

  methodCallerClassName_ = expression->TargetId()->Name();

  OnNodeExit(nodeName, expression->GetLocation());
}

void IrtBuilderVisitor::Visit(const NegateExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expNegate_);
  OnNodeEnter(nodeName, expression->GetLocation());

  expression->TargetExpression()->Accept(this);

  UpdateSubtreeWrapper(
      new Irt::NegateConditionalWrapper(std::move(subtreeWrapper_)));

  OnNodeExit(nodeName, expression->GetLocation());
}

/*__________ Statements __________*/

void IrtBuilderVisitor::Visit(const AssignIdStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statAssignId_);
  OnNodeEnter(nodeName, statement->GetLocation());

  statement->LeftPart()->Accept(this);
  std::unique_ptr<Irt::ISubtreeWrapper> wrapperLeftPart =
      std::move(subtreeWrapper_);
  statement->RightPart()->Accept(this);
  std::unique_ptr<Irt::ISubtreeWrapper> wrapperRightPart =
      std::move(subtreeWrapper_);

  UpdateSubtreeWrapper(new Irt::StatementWrapper(
      new Irt::MoveStatement(std::move(wrapperLeftPart->ToExpression()),
                             std::move(wrapperRightPart->ToExpression()))));

  OnNodeExit(nodeName, statement->GetLocation());
}

void IrtBuilderVisitor::Visit(const AssignIdWithIndexStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statAssignIdWithIndex_);
  OnNodeEnter(nodeName, statement->GetLocation());

  statement->LeftPartId()->Accept(this);
  std::unique_ptr<const Irt::Expression> leftPartExpression =
      std::move(subtreeWrapper_->ToExpression());

  statement->RightPart()->Accept(this);
  std::unique_ptr<const Irt::Expression> rightPartExpression =
      std::move(subtreeWrapper_->ToExpression());

  statement->LeftPartIndex()->Accept(this);
  std::unique_ptr<const Irt::Expression> indexExpression =
      std::move(subtreeWrapper_->ToExpression());

  UpdateSubtreeWrapper(new Irt::StatementWrapper(new Irt::MoveStatement(
      std::move(std::unique_ptr<const Irt::Expression>(
          new Irt::MemExpression(new Irt::BinaryExpression(
              Irt::OperatorTypes::Plus, std::move(leftPartExpression),
              std::move(std::unique_ptr<const Irt::Expression>(
                  new Irt::BinaryExpression(
                      Irt::OperatorTypes::Times,
                      new Irt::BinaryExpression(
                          Irt::OperatorTypes::Plus, std::move(indexExpression),
                          std::move(std::unique_ptr<const Irt::Expression>(
                              new Irt::ConstExpression(1)))),
                      new Irt::ConstExpression(
                          frameCurrent_->GetWordSize())))))))),
      std::move(rightPartExpression))));

  OnNodeExit(nodeName, statement->GetLocation());
}

void IrtBuilderVisitor::Visit(const PrintStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statPrint_);
  OnNodeEnter(nodeName, statement->GetLocation());

  statement->PrintTarget()->Accept(this);

  UpdateSubtreeWrapper(
      new Irt::ExpressionWrapper(std::move(frameCurrent_->ExternalCall(
          "print", std::move(std::unique_ptr<const Irt::ExpressionList>(
                       new Irt::ExpressionList(
                           std::move(subtreeWrapper_->ToExpression()))))))));

  OnNodeExit(nodeName, statement->GetLocation());
}

void IrtBuilderVisitor::Visit(const ConditionalStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statConditional_);
  OnNodeEnter(nodeName, statement->GetLocation());

  statement->Condition()->Accept(this);
  std::unique_ptr<Irt::ISubtreeWrapper> wrapperCondition =
      std::move(subtreeWrapper_);
  statement->PositiveTarget()->Accept(this);
  std::unique_ptr<Irt::ISubtreeWrapper> wrapperTargetPositive =
      std::move(subtreeWrapper_);
  statement->NegativeTarget()->Accept(this);
  std::unique_ptr<Irt::ISubtreeWrapper> wrapperTargetNegative =
      std::move(subtreeWrapper_);

  Address labelTrue;
  Address labelFalse;
  Address labelJoin;

  Address* resultLabelTrue = &labelJoin;
  Address* resultLabelFalse = &labelJoin;

  std::unique_ptr<const Irt::Statement> suffix(
      new Irt::LabelStatement(labelJoin));
  if (wrapperTargetNegative) {
    resultLabelFalse = &labelFalse;

    suffix =
        std::move(std::unique_ptr<const Irt::Statement>(new Irt::SeqStatement(
            new Irt::LabelStatement(labelFalse),
            new Irt::SeqStatement(
                std::move(wrapperTargetNegative->ToStatement()),
                std::move(suffix)))));
    if (wrapperTargetPositive) {
      suffix = std::move(std::unique_ptr<const Irt::Statement>(
          new Irt::SeqStatement(std::move(std::unique_ptr<const Irt::Statement>(
                                    new Irt::JumpStatement(labelJoin))),
                                std::move(suffix))));
    }
  }

  if (wrapperTargetPositive) {
    resultLabelTrue = &labelTrue;

    suffix =
        std::move(std::unique_ptr<const Irt::Statement>(new Irt::SeqStatement(
            new Irt::LabelStatement(labelTrue),
            new Irt::SeqStatement(
                std::move(wrapperTargetPositive->ToStatement()),
                std::move(suffix)))));
  }

  UpdateSubtreeWrapper(new Irt::StatementWrapper(
      new Irt::SeqStatement(std::move(wrapperCondition->ToConditional(
                                *resultLabelTrue, *resultLabelFalse)),
                            std::move(suffix))));

  OnNodeExit(nodeName, statement->GetLocation());
}

void IrtBuilderVisitor::Visit(const WhileLoopStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statWhileLoop_);
  OnNodeEnter(nodeName, statement->GetLocation());

  statement->Condition()->Accept(this);
  std::unique_ptr<Irt::ISubtreeWrapper> wrapperCondition =
      std::move(subtreeWrapper_);
  statement->Body()->Accept(this);
  std::unique_ptr<Irt::ISubtreeWrapper> wrapperBody =
      std::move(subtreeWrapper_);

  Address labelLoop;
  Address labelBody;
  Address labelDone;

  std::unique_ptr<const Irt::Statement> suffix(new Irt::SeqStatement(
      new Irt::JumpStatement(labelLoop), new Irt::LabelStatement(labelDone)));
  if (wrapperBody) {
    suffix =
        std::move(std::unique_ptr<const Irt::Statement>(new Irt::SeqStatement(
            std::move(wrapperBody->ToStatement()), std::move(suffix))));
  }

  UpdateSubtreeWrapper(new Irt::StatementWrapper(new Irt::SeqStatement(
      new Irt::LabelStatement(labelLoop),
      new Irt::SeqStatement(
          std::move(wrapperCondition->ToConditional(labelBody, labelDone)),
          std::move(std::unique_ptr<const Irt::Statement>(new Irt::SeqStatement(
              std::move(std::unique_ptr<const Irt::Statement>(
                  new Irt::LabelStatement(labelBody))),
              std::move(suffix))))))));

  OnNodeExit(nodeName, statement->GetLocation());
}

void IrtBuilderVisitor::Visit(const BracesStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statBraces_);
  OnNodeEnter(nodeName, statement->GetLocation());

  statement->List()->Accept(this);

  OnNodeExit(nodeName, statement->GetLocation());
}

/*__________ Type Modifiers __________*/

void IrtBuilderVisitor::Visit(const IntTypeModifier* typeModifier) {
  std::string nodeName = GenerateNodeName(NodeNames::typeModInt_);
  OnNodeEnter(nodeName, typeModifier->GetLocation());

  // such calls should never happen
  assert(false);

  OnNodeExit(nodeName, typeModifier->GetLocation());
}

void IrtBuilderVisitor::Visit(const BooleanTypeModifier* typeModifier) {
  std::string nodeName = GenerateNodeName(NodeNames::typeModeBool_);
  OnNodeEnter(nodeName, typeModifier->GetLocation());

  // such calls should never happen
  assert(false);

  OnNodeExit(nodeName, typeModifier->GetLocation());
}

void IrtBuilderVisitor::Visit(const IntArrayTypeModifier* typeModifier) {
  std::string nodeName = GenerateNodeName(NodeNames::typeModIntArray_);
  OnNodeEnter(nodeName, typeModifier->GetLocation());

  // such calls should never happen
  assert(false);

  OnNodeExit(nodeName, typeModifier->GetLocation());
}

void IrtBuilderVisitor::Visit(const IdTypeModifier* typeModifier) {
  std::string nodeName = GenerateNodeName(NodeNames::typeModeId_);
  OnNodeEnter(nodeName, typeModifier->GetLocation());

  // such calls should never happen
  assert(false);

  OnNodeExit(nodeName, typeModifier->GetLocation());
}

/*__________ Other (except lists) __________*/

void IrtBuilderVisitor::Visit(const VarDeclaration* declaration) {
  std::string nodeName = GenerateNodeName(NodeNames::varDecl_);
  OnNodeEnter(nodeName, declaration->GetLocation());

  // such calls should never happen
  assert(false);

  OnNodeExit(nodeName, declaration->GetLocation());
}

void IrtBuilderVisitor::Visit(const MethodArgument* argument) {
  std::string nodeName = GenerateNodeName(NodeNames::methArg_);
  OnNodeEnter(nodeName, argument->GetLocation());

  // such calls should never happen
  assert(false);

  OnNodeExit(nodeName, argument->GetLocation());
}

void IrtBuilderVisitor::Visit(const MethodDeclaration* declaration) {
  std::string nodeName = GenerateNodeName(NodeNames::methDecl_);
  OnNodeEnter(nodeName, declaration->GetLocation());

  BuildNewFrame(declaration);
  std::string methodFullName = MakeMethodFullName(
      frameCurrent_->GetClassName(), frameCurrent_->GetMethodName());

  declaration->Statements()->Accept(this);
  std::unique_ptr<Irt::ISubtreeWrapper> statementListWrapper =
      std::move(subtreeWrapper_);

  declaration->ReturnExpression()->Accept(this);
  std::unique_ptr<const Irt::Expression> expressionReturn =
      std::move(subtreeWrapper_->ToExpression());

  if (statementListWrapper) {
    UpdateSubtreeWrapper(new Irt::StatementWrapper(new Irt::SeqStatement(
        new Irt::LabelStatement(Address(methodFullName)),
        new Irt::SeqStatement(
            std::move(statementListWrapper->ToStatement()),
            std::move(
                std::unique_ptr<const Irt::Statement>(new Irt::MoveStatement(
                    std::move(
                        frameCurrent_->GetReturnValueAddress()->ToExpression()),
                    std::move(expressionReturn))))))));
  } else {
    UpdateSubtreeWrapper(new Irt::StatementWrapper(new Irt::SeqStatement(
        new Irt::LabelStatement(Address(methodFullName)),
        new Irt::MoveStatement(
            std::move(frameCurrent_->GetReturnValueAddress()->ToExpression()),
            std::move(expressionReturn)))));
  }

  OnNodeExit(nodeName, declaration->GetLocation());
}

void IrtBuilderVisitor::Visit(const MainClass* mainClass) {
  std::string nodeName = GenerateNodeName(NodeNames::mainClass_);
  OnNodeEnter(nodeName, mainClass->GetLocation());

  BuildNewFrame(mainClass);
  std::string methodFullName = MakeMethodFullName(
      frameCurrent_->GetClassName(), frameCurrent_->GetMethodName());

  mainClass->Statements()->Accept(this);
  std::unique_ptr<Irt::ISubtreeWrapper> statementListWrapper =
      std::move(subtreeWrapper_);
  if (statementListWrapper) {
    UpdateSubtreeWrapper(new Irt::StatementWrapper(new Irt::SeqStatement(
        std::move(std::unique_ptr<const Irt::Statement>(
            new Irt::LabelStatement(Address(methodFullName)))),
        std::move(statementListWrapper->ToStatement()))));
  } else {
    // empty function
    UpdateSubtreeWrapper(new Irt::StatementWrapper(
        new Irt::LabelStatement(Address(methodFullName))));
  }

  methodTrees_->emplace(methodFullName,
                        std::move(subtreeWrapper_->ToStatement()));

  OnNodeExit(nodeName, mainClass->GetLocation());
}

void IrtBuilderVisitor::Visit(const ClassDeclaration* declaration) {
  std::string nodeName = GenerateNodeName(NodeNames::classDecl_);
  OnNodeEnter(nodeName, declaration->GetLocation());

  classCurrentName_ = declaration->ClassName()->Name();
  declaration->MethodDeclarations()->Accept(this);

  OnNodeExit(nodeName, declaration->GetLocation());
}

void IrtBuilderVisitor::Visit(const Program* program) {
  std::string nodeName = GenerateNodeName(NodeNames::program_);
  OnNodeEnter(nodeName, program->GetLocation());

  program->GetMainClass()->Accept(this);
  program->ClassDeclarations()->Accept(this);

  OnNodeExit(nodeName, program->GetLocation());
}

/*__________  Lists __________*/

void IrtBuilderVisitor::Visit(const ExpressionList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::expList_);
  OnNodeEnter(nodeName, list->GetLocation());

  // such calls should never happen
  assert(false);

  OnNodeExit(nodeName, list->GetLocation());
}

void IrtBuilderVisitor::Visit(const StatementList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::statList_);
  OnNodeEnter(nodeName, list->GetLocation());

  const std::vector<std::unique_ptr<const Statement>>& statements =
      list->Statements();

  std::unique_ptr<Irt::ISubtreeWrapper> resultOnSuffix = nullptr;
  if (!statements.empty()) {
    // statements must be reversed before being used
    // we'll actually iterate over them in reversed order (the last statement
    // will be the first)
    (statements.front())->Accept(this);
    resultOnSuffix = std::move(subtreeWrapper_);
    for (auto it = std::next(statements.begin()); it != statements.end();
         ++it) {
      (*it)->Accept(this);
      std::unique_ptr<Irt::ISubtreeWrapper> resultCurrent =
          std::move(subtreeWrapper_);
      resultOnSuffix =
          std::unique_ptr<Irt::ISubtreeWrapper>(new Irt::StatementWrapper(
              new Irt::SeqStatement(std::move(resultCurrent->ToStatement()),
                                    std::move(resultOnSuffix->ToStatement()))));
    }
  }

  subtreeWrapper_ = std::move(resultOnSuffix);

  OnNodeExit(nodeName, list->GetLocation());
}

void IrtBuilderVisitor::Visit(const VarDeclarationList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::varDeclList_);
  OnNodeEnter(nodeName, list->GetLocation());

  // such calls should never happen
  assert(false);

  OnNodeExit(nodeName, list->GetLocation());
}

void IrtBuilderVisitor::Visit(const MethodArgumentList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::methAgrList_);
  OnNodeEnter(nodeName, list->GetLocation());

  // such calls should never happen
  assert(false);

  OnNodeExit(nodeName, list->GetLocation());
}

void IrtBuilderVisitor::Visit(const MethodDeclarationList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::methDeclList_);
  OnNodeEnter(nodeName, list->GetLocation());

  const std::vector<std::unique_ptr<const MethodDeclaration>>& methods =
      list->MethodDeclarations();

  for (auto it = methods.begin(); it != methods.end(); ++it) {
    (*it)->Accept(this);
    std::string methodFullName = MakeMethodFullName(
        frameCurrent_->GetClassName(), frameCurrent_->GetMethodName());
    methodTrees_->emplace(methodFullName,
                          std::move(subtreeWrapper_->ToStatement()));
  }

  OnNodeExit(nodeName, list->GetLocation());
}

void IrtBuilderVisitor::Visit(const ClassDeclarationList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::classDeclList_);
  OnNodeEnter(nodeName, list->GetLocation());

  const std::vector<std::unique_ptr<const ClassDeclaration>>& classes =
      list->ClassDeclarations();

  for (auto it = classes.begin(); it != classes.end(); ++it) {
    (*it)->Accept(this);
  }

  OnNodeExit(nodeName, list->GetLocation());
}

}  // namespace Ast
