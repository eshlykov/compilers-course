#pragma once

#include <algorithm>
#include <memory>
#include <vector>
#include "../../../utils/ct.hpp"
#include "../visitor.hpp"
#include "expression-call.hpp"
#include "move-call.hpp"
#include "statement-expression-list.hpp"

namespace Ct {

class Canonizer : public Visitor {
 public:
  Canonizer();

  virtual void Visit(BinaryOperator*) override final;

  virtual void Visit(Call*) override final;

  virtual void Visit(ConditionalJump*) override final;

  virtual void Visit(Constant*) override final;

  virtual void Visit(ExpressionSequence*) override final;

  virtual void Visit(Jump*) override final;

  virtual void Visit(Label*) override final;

  virtual void Visit(Memory*) override final;

  virtual void Visit(Move*) override final;

  virtual void Visit(Name*) override final;

  virtual void Visit(StatementSequence*) override final;

  virtual void Visit(Temporary*) override final;

  virtual void Visit(Void*) override final;

 private:
  bool IsConst(const std::shared_ptr<Statement>& statement) {
    auto voidStatement = std::dynamic_pointer_cast<Void>(statement);
    if (voidStatement == nullptr) {
      return false;
    }

    auto constStatement =
        std::dynamic_pointer_cast<Constant>(voidStatement->expression_);
    return constStatement != nullptr;
  }

  std::shared_ptr<Statement> Sequence(std::shared_ptr<Statement> first,
                                      std::shared_ptr<Statement> second) {
    if (IsConst(first)) {
      return second;
    }
    if (IsConst(second)) {
      return first;
    }
    return std::make_shared<StatementSequence>(first, second);
  }

  bool Commute(const std::shared_ptr<Statement>& first,
               const std::shared_ptr<Expression>& second) {
    auto nameStatement = std::dynamic_pointer_cast<Name>(second);
    auto constStatement = std::dynamic_pointer_cast<Constant>(second);
    return IsConst(first) || nameStatement != nullptr ||
           constStatement != nullptr;
  }

  std::shared_ptr<Statement> DoStatement(
      const std::shared_ptr<StatementSequence>& statement) {
    return Sequence(DoStatement(statement->leftStatement_),
                    DoStatement(statement->rightStatement_));
  }

  std::shared_ptr<Statement> DoStatement(
      const std::shared_ptr<Move>& moveStatement) {
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

  std::shared_ptr<Statement> DoStatement(
      const std::shared_ptr<Void>& voidStatement) {
    auto call = std::dynamic_pointer_cast<Call>(voidStatement);
    if (call != nullptr) {
      return ReorderStatement(std::make_shared<ExpressionCall>(call));
    }

    return ReorderStatement(voidStatement);
  }

  std::shared_ptr<Statement> DoStatement(
      const std::shared_ptr<Statement>& statement) {
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

  std::shared_ptr<Statement> ReorderStatement(
      const std::shared_ptr<Statement>& statement) {
    std::shared_ptr<StatementExpressionList> list = Reorder(statement->Kids());
    return Sequence(list->Statement_, statement->Build(list->Expressions_));
  }

  std::shared_ptr<ExpressionSequence> DoExpression(
      const std::shared_ptr<ExpressionSequence>& expressionSequence) {
    std::shared_ptr<Statement> statements =
        DoStatement(expressionSequence->statement_);
    std::shared_ptr<ExpressionSequence> expression =
        DoExpression(expressionSequence->expression_);
    return std::make_shared<ExpressionSequence>(
        Sequence(statements, expression->statement_), expression->expression_);
  }

  std::shared_ptr<ExpressionSequence> DoExpression(
      const std::shared_ptr<Expression>& expression) {
    auto expressionSequence =
        std::dynamic_pointer_cast<ExpressionSequence>(expression);
    if (expressionSequence != nullptr) {
      return DoExpression(expressionSequence);
    }

    return ReorderExpression(expression);
  }

  std::shared_ptr<ExpressionSequence> ReorderExpression(
      const std::shared_ptr<Expression>& expression) {
    std::shared_ptr<StatementExpressionList> list = Reorder(expression->Kids());
    return std::make_shared<ExpressionSequence>(
        list->Statement_, expression->Build(list->Expressions_));
  }

  std::shared_ptr<StatementExpressionList> Reorder(
      const std::vector<std::shared_ptr<Expression>>& list) {
    if (list.empty()) {
      return NopNull;
    }

    std::shared_ptr<Expression> head = list.front();

    auto callExpression = std::dynamic_pointer_cast<Call>(head);
    if (callExpression != nullptr) {
      Storage storage;
      std::shared_ptr<Expression> justExpression =
          std::make_shared<ExpressionSequence>(
              std::make_shared<Move>(std::make_shared<Temporary>(storage),
                                     head),
              std::make_shared<Temporary>(storage));
      std::vector<std::shared_ptr<Expression>> listCopy = list;
      listCopy.front() = justExpression;
      return Reorder(listCopy);
    }

    std::shared_ptr<ExpressionSequence> expressionSequence = DoExpression(head);
    std::vector<std::shared_ptr<Expression>> listSinceSecond;
    std::copy(list.begin() + 1, list.end(),
              std::back_inserter(listSinceSecond));
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
        Sequence(expressionSequence->statement_,
                 Sequence(std::make_shared<Move>(
                              std::make_shared<Temporary>(storage),
                              expressionSequence->expression_),
                          statementExpressionList->Statement_)),
        newList);
  }

  std::vector<std::shared_ptr<Statement>> Linearize(
      const std::shared_ptr<StatementSequence>& statement,
      const std::vector<std::shared_ptr<Statement>>& list) {
    return Linearize(statement->leftStatement_,
                     Linearize(statement->rightStatement_, list));
  }

  std::vector<std::shared_ptr<Statement>> Linearize(
      const std::shared_ptr<Statement>& statement,
      const std::vector<std::shared_ptr<Statement>>& list) {
    auto statementSequence =
        std::dynamic_pointer_cast<StatementSequence>(statement);
    if (statementSequence != nullptr) {
      return Linearize(statementSequence, list);
    }

    std::vector<std::shared_ptr<Statement>> listCopy{statement};
    std::copy(list.begin(), list.end(), std::back_inserter(listCopy));
    return listCopy;
  }

  std::vector<std::shared_ptr<Statement>> Linearize(
      const std::shared_ptr<Statement>& statement) {
    return Linearize(DoStatement(statement),
                     std::vector<std::shared_ptr<Statement>>());
  }

 private:
  const std::shared_ptr<StatementExpressionList> NopNull =
      std::make_shared<StatementExpressionList>(
          std::make_shared<Void>(std::make_shared<Constant>(0)),
          std::vector<std::shared_ptr<Expression>>());
  std::shared_ptr<Node> node_;
};

}  // namespace Ct
