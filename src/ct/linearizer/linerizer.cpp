#include "linerizer.hpp"

namespace Ct {

std::vector<StatementPtr> Linearizer::Linearize(const StatementPtr& statement) {
  return Linearize(DoStatement(statement), std::vector<StatementPtr>());
}

bool Linearizer::IsNop(const StatementPtr& statement) {
  auto voidStatement = std::dynamic_pointer_cast<Void>(statement);
  if (voidStatement == nullptr) {
    return false;
  }

  auto constStatement =
      std::dynamic_pointer_cast<Constant>(voidStatement->expression_);
  return constStatement != nullptr;
}

StatementPtr Linearizer::Sequence(StatementPtr first, StatementPtr second) {
  if (IsNop(first)) {
    return second;
  }
  if (IsNop(second)) {
    return first;
  }
  return std::make_shared<StatementSequence>(first, second);
}

bool Linearizer::Commute(const StatementPtr& first,
                         const ExpressionPtr& second) {
  auto nameStatement = std::dynamic_pointer_cast<Name>(second);
  auto constStatement = std::dynamic_pointer_cast<Constant>(second);
  return IsNop(first) || nameStatement != nullptr || constStatement != nullptr;
}

StatementPtr Linearizer::DoStatement(const StatementSequencePtr& statement) {
  return Sequence(DoStatement(statement->leftStatement_),
                  DoStatement(statement->rightStatement_));
}

StatementPtr Linearizer::DoStatement(const MovePtr& moveStatement) {
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

StatementPtr Linearizer::DoStatement(const VoidPtr& voidStatement) {
  auto call = std::dynamic_pointer_cast<Call>(voidStatement);
  if (call != nullptr) {
    return ReorderStatement(std::make_shared<ExpressionCall>(call));
  }

  return ReorderStatement(voidStatement);
}

StatementPtr Linearizer::DoStatement(const StatementPtr& statement) {
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

StatementPtr Linearizer::ReorderStatement(const StatementPtr& statement) {
  std::shared_ptr<StatementExpressionList> list = Reorder(statement->Kids());
  return Sequence(list->Statement_, statement->Build(list->Expressions_));
}

ExpressionSequencePtr Linearizer::DoExpression(
    const ExpressionSequencePtr& expressionSequence) {
  StatementPtr statements = DoStatement(expressionSequence->statement_);
  ExpressionSequencePtr expression =
      DoExpression(expressionSequence->expression_);
  return std::make_shared<ExpressionSequence>(
      Sequence(statements, expression->statement_), expression->expression_);
}

ExpressionSequencePtr Linearizer::DoExpression(
    const ExpressionPtr& expression) {
  auto expressionSequence =
      std::dynamic_pointer_cast<ExpressionSequence>(expression);
  if (expressionSequence != nullptr) {
    return DoExpression(expressionSequence);
  }

  return ReorderExpression(expression);
}

ExpressionSequencePtr Linearizer::ReorderExpression(
    const ExpressionPtr& expression) {
  std::shared_ptr<StatementExpressionList> list = Reorder(expression->Kids());
  return std::make_shared<ExpressionSequence>(
      list->Statement_, expression->Build(list->Expressions_));
}

std::shared_ptr<StatementExpressionList> Linearizer::Reorder(
    const std::vector<ExpressionPtr>& list) {
  if (list.empty()) {
    return NopNull;
  }

  ExpressionPtr head = list.front();

  auto callExpression = std::dynamic_pointer_cast<Call>(head);
  if (callExpression != nullptr) {
    Storage storage;
    ExpressionPtr justExpression = std::make_shared<ExpressionSequence>(
        std::make_shared<Move>(std::make_shared<Temporary>(storage), head),
        std::make_shared<Temporary>(storage));
    std::vector<ExpressionPtr> listCopy = list;
    listCopy.front() = justExpression;
    return Reorder(listCopy);
  }

  ExpressionSequencePtr expressionSequence = DoExpression(head);
  std::vector<ExpressionPtr> listSinceSecond;
  std::copy(list.begin() + 1, list.end(), std::back_inserter(listSinceSecond));
  std::shared_ptr<StatementExpressionList> statementExpressionList =
      Reorder(listSinceSecond);
  if (Commute(statementExpressionList->Statement_,
              expressionSequence->expression_)) {
    std::vector<ExpressionPtr> newList{expressionSequence->expression_};
    std::copy(statementExpressionList->Expressions_.begin(),
              statementExpressionList->Expressions_.end(),
              std::back_inserter(newList));
    return std::make_shared<StatementExpressionList>(
        Sequence(expressionSequence->statement_,
                 statementExpressionList->Statement_),
        newList);
  }

  Storage storage;
  std::vector<ExpressionPtr> newList{std::make_shared<Temporary>(storage)};
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

std::vector<StatementPtr> Linearizer::Linearize(
    const StatementSequencePtr& statement,
    const std::vector<StatementPtr>& list) {
  return Linearize(statement->leftStatement_,
                   Linearize(statement->rightStatement_, list));
}

std::vector<StatementPtr> Linearizer::Linearize(
    const StatementPtr& statement, const std::vector<StatementPtr>& list) {
  auto statementSequence =
      std::dynamic_pointer_cast<StatementSequence>(statement);
  if (statementSequence != nullptr) {
    return Linearize(statementSequence, list);
  }

  std::vector<StatementPtr> listCopy{statement};
  std::copy(list.begin(), list.end(), std::back_inserter(listCopy));
  return listCopy;
}

}  // namespace Ct
