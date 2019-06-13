#include <cg/node/patterns.hpp>

#include <limits>

#include <cg/node/commands.hpp>
#include <cg/visitor/typing-visitor.hpp>
#include <irt/node/expression.hpp>

using namespace Cg;

template <typename T>
Pattern::ValidAndValue<const T*> Pattern::GetTypedNode(const IrtVt* node) {
  TypingVisitor<T> visitor;
  node->Accept(&visitor);
  const T* pointer = visitor.GetNode();
  return ValidAndValue<const T*>(pointer != nullptr, pointer);
}

int Pattern::GetDynamicPrice(const IrtVt* node) {
  auto iterator = dynamic_->find(node);
  if (iterator == dynamic_->end()) {
    return std::numeric_limits<int>::max();
  }
  return iterator->second.first;
}

const Cg::Expression* Pattern::GetDynamicValue(const IrtVt* node) {
  return dynamic_cast<const Expression*>(
      dynamic_->find(node)->second.second.get());
}

template <typename Command>
void Pattern::ConsumeBinaryOperation(const IrtVt* node,
                                     Irt::OperatorTypes operation) {
  auto root = GetTypedNode<BinaryExpression>(node);
  if (!root.IsValid() || root->Operation() != operation) {
    return;
  }

  const int price = GetDynamicPrice(root->LeftOperand()) +
                    GetDynamicPrice(root->RightOperand()) + 1;
  if (GetDynamicPrice(*root) > price) {
    (*dynamic_)[*root] =
        std::make_pair(price, std::unique_ptr<const Expression>(new Command(
                                  GetDynamicValue(root->LeftOperand()),
                                  GetDynamicValue(root->RightOperand()))));
  }
}

void TempPattern::Consume(const IrtVt* node) {
  const auto root = GetTypedNode<Irt::TempExpression>(node);
  if (!root.IsValid()) {
    return;
  }

  (*dynamic_)[*root] = std::make_pair(
      1, std::unique_ptr<const Expression>(
             new Cg::TempExpression(root->GetStorage().ToString())));
}

void LabelPattern::Consume(const IrtVt* node) {
  const auto root = GetTypedNode<Irt::LabelStatement>(node);

  if (!root.IsValid()) {
    return;
  }

  (*dynamic_)[*root] = std::make_pair(
      1, std::unique_ptr<const Command>(
             new Cg::LabelDeclarationCommand(root->Label().ToString())));
}

void AddPattern::Consume(const IrtVt* node) {
  ConsumeBinaryOperation<AddCommand>(node, Irt::OperatorTypes::Plus);
}

void SubPattern::Consume(const IrtVt* node) {
  ConsumeBinaryOperation<SubCommand>(node, Irt::OperatorTypes::Minus);
}

void MultPattern::Consume(const IrtVt* node) {
  ConsumeBinaryOperation<MultCommand>(node, Irt::OperatorTypes::Times);
}

void DivPattern::Consume(const IrtVt* node) {
  ConsumeBinaryOperation<DivCommand>(node, Irt::OperatorTypes::Div);
}

void SubConstPattern::Consume(const IrtVt* node) {
  const auto root = GetTypedNode<BinaryExpression>(node);
  if (!root.IsValid() || root->Operation() != Irt::OperatorTypes::Minus) {
    return;
  }

  const Irt::Expression* left = root->LeftOperand();
  const Irt::Expression* right = root->RightOperand();

  const auto rightConst = GetTypedNode<ConstExpression>(node);
  if (!rightConst.IsValid()) {
    return;
  }

  const int price = GetDynamicPrice(left) + 1;

  if (GetDynamicPrice(*root) > price) {
    (*dynamic_)[*root] = std::make_pair(
        price, std::unique_ptr<const Expression>(new SubConstCommand(
                   GetDynamicValue(left), rightConst->Value())));
  }
}

void AddConstLeftPattern::Consume(const IrtVt* node) {
  const auto root = GetTypedNode<BinaryExpression>(node);
  if (!root.IsValid() || root->Operation() != Irt::OperatorTypes::Plus) {
    return;
  }

  const Irt::Expression* left = root->LeftOperand();
  const Irt::Expression* right = root->RightOperand();

  const auto leftConst = GetTypedNode<ConstExpression>(node);
  if (!leftConst.IsValid()) {
    return;
  }

  const int price = GetDynamicPrice(right) + 1;

  if (GetDynamicPrice(*root) > price) {
    (*dynamic_)[*root] = std::make_pair(
        price, std::unique_ptr<const Expression>(new AddConstCommand(
                   GetDynamicValue(right), leftConst->Value())));
  }
}

void AddConstRightPattern::Consume(const IrtVt* node) {
  const auto root = GetTypedNode<BinaryExpression>(node);
  if (!root.IsValid() || root->Operation() != Irt::OperatorTypes::Plus) {
    return;
  }

  const Irt::Expression* left = root->LeftOperand();
  const Irt::Expression* right = root->RightOperand();

  const auto rightConst = GetTypedNode<ConstExpression>(node);
  if (!rightConst.IsValid()) {
    return;
  }

  const int price = GetDynamicPrice(left) + 1;

  if (GetDynamicPrice(*root) > price) {
    (*dynamic_)[*root] = std::make_pair(
        price, std::unique_ptr<const Expression>(new AddConstCommand(
                   GetDynamicValue(left), rightConst->Value())));
  }
}

void ConstPattern::Consume(const IrtVt* node) {
  const auto root = GetTypedNode<ConstExpression>(node);
  if (!root.IsValid()) {
    return;
  }

  const int price = 1;

  if (GetDynamicPrice(*root) > price) {
    (*dynamic_)[*root] = std::make_pair(
        price, std::unique_ptr<const Expression>(
                   new AddConstCommand(new NullExpression(), root->Value())));
  }
}

void LoadMemoryPattern::Consume(const IrtVt* node) {
  const auto root = GetTypedNode<MemExpression>(node);
  if (!root.IsValid()) {
    return;
  }
  const Irt::Expression* value = root->Address();
  const int price = GetDynamicPrice(value) + 1;

  if (GetDynamicPrice(*root) > price) {
    (*dynamic_)[*root] =
        std::make_pair(price, std::unique_ptr<const Expression>(
                                  new LoadCommand(GetDynamicValue(value), 0)));
  }
}

void LoadConstMemoryPattern::Consume(const IrtVt* node) {
  const auto root = GetTypedNode<MemExpression>(node);
  if (!root.IsValid()) {
    return;
  }
  const Irt::Expression* value = root->Address();
  const auto constValue = GetTypedNode<ConstExpression>(value);
  if (!constValue.IsValid()) {
    return;
  }
  const int price = 1;

  if (GetDynamicPrice(*root) > price) {
    (*dynamic_)[*root] =
        std::make_pair(price, std::unique_ptr<const Expression>(new LoadCommand(
                                  new NullExpression(), constValue->Value())));
  }
}

void LoadMemoryLeftOffsetPattern::Consume(const IrtVt* node) {
  const auto root = GetTypedNode<MemExpression>(node);
  if (!root.IsValid()) {
    return;
  }
  const Irt::Expression* child = root->Address();
  const auto expression = GetTypedNode<BinaryExpression>(child);
  if (!expression.IsValid() ||
      expression->Operation() != Irt::OperatorTypes::Plus) {
    return;
  }

  const Irt::Expression* left = expression->LeftOperand();
  const Irt::Expression* right = expression->RightOperand();

  const auto leftConst = GetTypedNode<ConstExpression>(node);
  if (!leftConst.IsValid()) {
    return;
  }

  const int price = GetDynamicPrice(right) + 1;

  if (GetDynamicPrice(*root) > price) {
    (*dynamic_)[*root] =
        std::make_pair(price, std::unique_ptr<const Expression>(new LoadCommand(
                                  GetDynamicValue(right), leftConst->Value())));
  }
}

void LoadMemoryRightOffsetPattern::Consume(const IrtVt* node) {
  const auto root = GetTypedNode<MemExpression>(node);
  if (!root.IsValid()) {
    return;
  }
  const Irt::Expression* child = root->Address();
  const auto expression = GetTypedNode<BinaryExpression>(child);
  if (!expression.IsValid() ||
      expression->Operation() != Irt::OperatorTypes::Plus) {
    return;
  }

  const Irt::Expression* left = expression->LeftOperand();
  const Irt::Expression* right = expression->RightOperand();

  const auto rightConst = GetTypedNode<ConstExpression>(node);
  if (!rightConst.IsValid()) {
    return;
  }

  const int price = GetDynamicPrice(left) + 1;

  if (GetDynamicPrice(*root) > price) {
    (*dynamic_)[*root] =
        std::make_pair(price, std::unique_ptr<const Expression>(new LoadCommand(
                                  GetDynamicValue(left), rightConst->Value())));
  }
}

void StoreMemoryPattern::Consume(const IrtVt* node) {
  const auto root = GetTypedNode<MoveStatement>(node);
  if (!root.IsValid()) {
    return;
  }
  const Irt::Expression* dest = root->Destination();
  const Irt::Expression* source = root->Source();

  const auto destValue = GetTypedNode<MemExpression>(dest);
  if (!destValue.IsValid()) {
    return;
  }

  const int price =
      GetDynamicPrice(destValue->Address()) + GetDynamicPrice(source) + 1;

  if (GetDynamicPrice(*root) > price) {
    (*dynamic_)[*root] = std::make_pair(
        price, std::unique_ptr<const Statement>(new StoreCommand(
                   GetDynamicValue(dest), 0, GetDynamicValue(source))));
  }
}

void StoreConstMemoryPattern::Consume(const IrtVt* node) {
  const auto root = GetTypedNode<MoveStatement>(node);
  if (!root.IsValid()) {
    return;
  }
  const Irt::Expression* dest = root->Destination();
  const Irt::Expression* source = root->Source();

  const auto destValue = GetTypedNode<MemExpression>(dest);
  if (!destValue.IsValid()) {
    return;
  }
  const Irt::Expression* destChild = destValue->Address();
  const auto constValue = GetTypedNode<ConstExpression>(destChild);
  if (!constValue.IsValid()) {
    return;
  }

  const int price = GetDynamicPrice(source) + 1;

  if (GetDynamicPrice(*root) > price) {
    (*dynamic_)[*root] =
        std::make_pair(price, std::unique_ptr<const Statement>(new StoreCommand(
                                  new NullExpression(), constValue->Value(),
                                  GetDynamicValue(source))));
  }
}

void StoreMemoryRightOffsetPattern::Consume(const IrtVt* node) {
  const auto root = GetTypedNode<MoveStatement>(node);
  if (!root.IsValid()) {
    return;
  }
  const Irt::Expression* dest = root->Destination();
  const Irt::Expression* source = root->Source();

  const auto memValue = GetTypedNode<MemExpression>(dest);
  if (!memValue.IsValid()) {
    return;
  }
  const auto memExpressionValue =
      GetTypedNode<BinaryExpression>(memValue->Address());
  if (!memExpressionValue.IsValid() ||
      memExpressionValue->Operation() != Irt::OperatorTypes::Plus) {
    return;
  }
  const Irt::Expression* left = memExpressionValue->LeftOperand();
  const Irt::Expression* right = memExpressionValue->RightOperand();

  const auto leftConst = GetTypedNode<ConstExpression>(left);
  if (!leftConst.IsValid()) {
    return;
  }

  const int price = GetDynamicPrice(right) + GetDynamicPrice(source) + 1;

  if (GetDynamicPrice(*root) > price) {
    (*dynamic_)[*root] =
        std::make_pair(price, std::unique_ptr<const Statement>(new StoreCommand(
                                  GetDynamicValue(dest), leftConst->Value(),
                                  GetDynamicValue(source))));
  }
}

void StoreMemoryLeftOffsetPattern::Consume(const IrtVt* node) {
  const auto root = GetTypedNode<MoveStatement>(node);
  if (!root.IsValid()) {
    return;
  }
  const Irt::Expression* dest = root->Destination();
  const Irt::Expression* source = root->Source();

  const auto memValue = GetTypedNode<MemExpression>(dest);
  if (!memValue.IsValid()) {
    return;
  }
  const auto memExpressionValue =
      GetTypedNode<BinaryExpression>(memValue->Address());
  if (!memExpressionValue.IsValid() ||
      memExpressionValue->Operation() != Irt::OperatorTypes::Plus) {
    return;
  }
  const Irt::Expression* left = memExpressionValue->LeftOperand();
  const Irt::Expression* right = memExpressionValue->RightOperand();

  const auto rightConst = GetTypedNode<ConstExpression>(right);
  if (!rightConst.IsValid()) {
    return;
  }

  const int price = GetDynamicPrice(left) + GetDynamicPrice(source) + 1;

  if (GetDynamicPrice(*root) > price) {
    (*dynamic_)[*root] =
        std::make_pair(price, std::unique_ptr<const Statement>(new StoreCommand(
                                  GetDynamicValue(dest), rightConst->Value(),
                                  GetDynamicValue(source))));
  }
}

void StoreRegisterPattern::Consume(const IrtVt* node) {
  const auto root = GetTypedNode<MoveStatement>(node);
  if (!root.IsValid()) {
    return;
  }
  const Irt::Expression* dest = root->Destination();
  const Irt::Expression* source = root->Source();

  const auto destValue = GetTypedNode<Irt::TempExpression>(dest);
  if (!destValue.IsValid()) {
    return;
  }

  const int price = GetDynamicPrice(source) + 1;

  if (GetDynamicPrice(*root) > price) {
    (*dynamic_)[*root] = std::make_pair(
        price, std::unique_ptr<const Statement>(new MoveRegisterCommand(
                   new Cg::TempExpression(destValue->GetStorage().ToString()),
                   GetDynamicValue(source))));
  }
}

void CallFunctionPattern::Consume(const IrtVt* node) {
  const auto root = GetTypedNode<CallExpression>(node);
  if (!root.IsValid()) {
    return;
  }

  const auto function = GetTypedNode<NameExpression>(root->Function());
  const std::vector<std::unique_ptr<const Irt::Expression> >& arguments =
      root->Arguments()->Expressions();

  int price = 1;

  std::vector<const Cg::Expression*> commandArguments;
  for (unsigned int i = 0; i < arguments.size(); i++) {
    price += GetDynamicPrice(arguments[i].get());
    commandArguments.push_back(GetDynamicValue(arguments[i].get()));
  }
  (*dynamic_)[*root] = std::make_pair(
      price, std::unique_ptr<const Expression>(new CallFunctionCommand(
                 function->GetAddress().ToString(), commandArguments)));
}

void JumpPattern::Consume(const IrtVt* node) {
  const auto root = GetTypedNode<JumpStatement>(node);

  if (!root.IsValid()) {
    return;
  }

  std::string targetLabel = root->Target().ToString();

  const int price = 1;

  (*dynamic_)[*root] = std::make_pair(
      price, std::unique_ptr<const Statement>(new JumpCommand(targetLabel)));
}

void ConditionalJumpPattern::Consume(const IrtVt* node) {
  const auto root = GetTypedNode<JumpConditionalStatement>(node);

  if (!root.IsValid()) {
    return;
  }

  const Irt::Expression* leftOperand = root->LeftOperand();
  const Irt::Expression* rightOperand = root->RightOperand();

  const int price =
      GetDynamicPrice(leftOperand) + GetDynamicPrice(rightOperand) + 1;

  if (GetDynamicPrice(*root) > price) {
    (*dynamic_)[*root] = std::make_pair(
        price, std::unique_ptr<const Statement>(new ConditionalJumpCommand(
                   GetDynamicValue(leftOperand), GetDynamicValue(rightOperand),
                   root->Operation(), root->TrueLabel().ToString(),
                   root->FalseLabel().ToString())));
  }
}

void ExpStatementPattern::Consume(const IrtVt* node) {
  const auto root = GetTypedNode<ExpStatement>(node);

  if (!root.IsValid()) {
    return;
  }

  const Irt::Expression* expression = root->GetExpression();

  const int price = GetDynamicPrice(expression);

  if (GetDynamicPrice(*root) > price) {
    (*dynamic_)[*root] = std::make_pair(
        price, std::unique_ptr<const Statement>(
                   new ExpStatementCommand(GetDynamicValue(expression))));
  }
}
