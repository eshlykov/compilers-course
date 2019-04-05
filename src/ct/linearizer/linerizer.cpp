#include "linerizer.hpp"

namespace Ct {

std::vector<std::shared_ptr<Statement>> Linearizer::Linearize(
    const std::shared_ptr<Statement> &statement) {
  return Linearize(DoStatement(statement),
                   std::vector<std::shared_ptr<Statement>>());
}

bool Linearizer::IsNop(const std::shared_ptr<Statement> &statement) {
  auto voidStatement = std::dynamic_pointer_cast<Void>(statement);
  if (voidStatement == nullptr) {
    return false;
  }

  auto constStatement =
      std::dynamic_pointer_cast<Constant>(voidStatement->expression_);
  return constStatement != nullptr;
}

std::shared_ptr<Statement> Linearizer::Sequence(
    std::shared_ptr<Statement> first, std::shared_ptr<Statement> second) {
  if (IsNop(first)) {
    return second;
  }
  if (IsNop(second)) {
    return first;
  }
  return std::make_shared<StatementSequence>(first, second);
}

bool Linearizer::Commute(const std::shared_ptr<Statement> &first,
                         const std::shared_ptr<Expression> &second) {
  auto nameStatement = std::dynamic_pointer_cast<Name>(second);
  auto constStatement = std::dynamic_pointer_cast<Constant>(second);
  return IsNop(first) || nameStatement != nullptr || constStatement != nullptr;
}

std::shared_ptr<Statement> Linearizer::DoStatement(
    const std::shared_ptr<StatementSequence> &statement) {
  return Sequence(DoStatement(statement->leftStatement_),
                  DoStatement(statement->rightStatement_));
}

std::shared_ptr<Statement> Linearizer::DoStatement(
    const std::shared_ptr<Move> &moveStatement) {
  auto temporary =
      std::dynamic_pointer_cast<Temporary>(moveStatement->destination_);
  auto call = std::dynamic_pointer_cast<Call>(moveStatement->source_);
  if (temporary != nullptr && call != nullptr) {
    return ReorderStatement(std::make_shared<MoveCall>(temporary, call));
  }

  auto expressionSequence = std::dynamic_pointer_cast<ExpressionSequence>(
      moveStatement->destination_);
  if (expressionSequence != nullptr) {
    return DoStatement(std::make_shared<StatementSequence>(
        expressionSequence->statement_,
        std::make_shared<Move>(expressionSequence->expression_,
                               moveStatement->source_)));
  }

  return ReorderStatement(moveStatement);
}

std::shared_ptr<Statement> Linearizer::DoStatement(
    const std::shared_ptr<Void> &voidStatement) {
  auto call = std::dynamic_pointer_cast<Call>(voidStatement);
  if (call != nullptr) {
    return ReorderStatement(std::make_shared<ExpressionCall>(call));
  }

  return ReorderStatement(voidStatement);
}

std::shared_ptr<Statement> Linearizer::DoStatement(
    const std::shared_ptr<Statement> &statement) {
  auto statementSequence =
      std::dynamic_pointer_cast<StatementSequence>(statement);
  if (statementSequence != nullptr) {
    return DoStatement(statementSequence);
  }

  auto moveStatement = std::dynamic_pointer_cast<Move>(statement);
  if (moveStatement != nullptr) {
    return DoStatement(moveStatement);
  }

  auto voidStatement = std::dynamic_pointer_cast<Void>(statement);
  if (voidStatement != nullptr) {
    return DoStatement(voidStatement);
  }

  return ReorderStatement(statement);
}

std::shared_ptr<Statement> Linearizer::ReorderStatement(
    const std::shared_ptr<Statement> &statement) {
  std::shared_ptr<StatementExpressionList> list = Reorder(statement->Kids());
  return Sequence(list->Statement_, statement->Build(list->Expressions_));
}

std::shared_ptr<ExpressionSequence> Linearizer::DoExpression(
    const std::shared_ptr<ExpressionSequence> &expressionSequence) {
  std::shared_ptr<Statement> statements =
      DoStatement(expressionSequence->statement_);
  std::shared_ptr<ExpressionSequence> expression =
      DoExpression(expressionSequence->expression_);
  return std::make_shared<ExpressionSequence>(
      Sequence(statements, expression->statement_), expression->expression_);
}

std::shared_ptr<ExpressionSequence> Linearizer::DoExpression(
    const std::shared_ptr<Expression> &expression) {
  auto expressionSequence =
      std::dynamic_pointer_cast<ExpressionSequence>(expression);
  if (expressionSequence != nullptr) {
    return DoExpression(expressionSequence);
  }

  return ReorderExpression(expression);
}

std::shared_ptr<ExpressionSequence> Linearizer::ReorderExpression(
    const std::shared_ptr<Expression> &expression) {
  std::shared_ptr<StatementExpressionList> list = Reorder(expression->Kids());
  return std::make_shared<ExpressionSequence>(
      list->Statement_, expression->Build(list->Expressions_));
}

std::shared_ptr<StatementExpressionList> Linearizer::Reorder(
    const std::vector<std::shared_ptr<Expression>> &list) {
  if (list.empty()) {
    return NopNull;
  }

  std::shared_ptr<Expression> head = list.front();

  auto callExpression = std::dynamic_pointer_cast<Call>(head);
  if (callExpression != nullptr) {
    Storage storage;
    std::shared_ptr<Expression> justExpression =
        std::make_shared<ExpressionSequence>(
            std::make_shared<Move>(std::make_shared<Temporary>(storage), head),
            std::make_shared<Temporary>(storage));
    std::vector<std::shared_ptr<Expression>> listCopy = list;
    listCopy.front() = justExpression;
    return Reorder(listCopy);
  }

  std::shared_ptr<ExpressionSequence> expressionSequence = DoExpression(head);
  std::vector<std::shared_ptr<Expression>> listSinceSecond;
  std::copy(list.begin() + 1, list.end(), std::back_inserter(listSinceSecond));
  std::shared_ptr<StatementExpressionList> statementExpressionList =
      Reorder(listSinceSecond);
  if (Commute(statementExpressionList->Statement_,
              expressionSequence->expression_)) {
    std::vector<std::shared_ptr<Expression>> newList{
        expressionSequence->expression_};
    std::copy(statementExpressionList->Expressions_.begin(),
              statementExpressionList->Expressions_.end(),
              std::back_inserter(newList));
    return std::make_shared<StatementExpressionList>(
        Sequence(expressionSequence->statement_,
                 statementExpressionList->Statement_),
        newList);
  }

  Storage storage;
  std::vector<std::shared_ptr<Expression>> newList{
      std::make_shared<Temporary>(storage)};
  std::copy(statementExpressionList->Expressions_.begin(),
            statementExpressionList->Expressions_.end(),
            std::back_inserter(newList));
  return std::make_shared<StatementExpressionList>(
      Sequence(
          expressionSequence->statement_,
          Sequence(std::make_shared<Move>(std::make_shared<Temporary>(storage),
                                          expressionSequence->expression_),
                   statementExpressionList->Statement_)),
      newList);
}

std::vector<std::shared_ptr<Statement>> Linearizer::Linearize(
    const std::shared_ptr<StatementSequence> &statement,
    const std::vector<std::shared_ptr<Statement>> &list) {
  return Linearize(statement->leftStatement_,
                   Linearize(statement->rightStatement_, list));
}

std::vector<std::shared_ptr<Statement>> Linearizer::Linearize(
    const std::shared_ptr<Statement> &statement,
    const std::vector<std::shared_ptr<Statement>> &list) {
  auto statementSequence =
      std::dynamic_pointer_cast<StatementSequence>(statement);
  if (statementSequence != nullptr) {
    return Linearize(statementSequence, list);
  }

  std::vector<std::shared_ptr<Statement>> listCopy{statement};
  std::copy(list.begin(), list.end(), std::back_inserter(listCopy));
  return listCopy;
}

}  // namespace Ct
