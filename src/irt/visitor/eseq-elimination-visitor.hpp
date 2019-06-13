#pragma once

#include <cassert>
#include <memory>

#include <irt/node/node-names.hpp>
#include <irt/visitor/visitor.hpp>

#include <irt/node/expression-list.hpp>
#include <irt/node/expression.hpp>
#include <irt/node/statement.hpp>

namespace Irt {

class EseqEliminationVisitor : public Visitor {
 public:
  EseqEliminationVisitor(bool verbose = false) : Visitor(verbose) {}
  ~EseqEliminationVisitor() {}

  std::unique_ptr<const Statement> ResultTree();
  std::unique_ptr<const Statement> ResultStatementTree();
  std::unique_ptr<const Expression> ResultExpressionTree();

  // Visitors for different node types.
  void Visit(const ConstExpression* expression) override;
  void Visit(const NameExpression* expression) override;
  void Visit(const TempExpression* expression) override;
  void Visit(const BinaryExpression* expression) override;
  void Visit(const MemExpression* expression) override;
  void Visit(const CallExpression* expression) override;
  void Visit(const EseqExpression* expression) override;

  void Visit(const ExpStatement* statement) override;
  void Visit(const JumpConditionalStatement* statement) override;
  void Visit(const JumpStatement* statement) override;
  void Visit(const LabelStatement* statement) override;
  void Visit(const MoveStatement* statement) override;
  void Visit(const SeqStatement* statement) override;

  void Visit(const ExpressionList* list) override;
  void Visit(const StatementList* list) override;

 private:
  void UpdateLastExpression(const Expression* newLastExpression);
  void UpdateLastExpression(
      std::unique_ptr<const Expression> newLastExpression);

  void UpdateLastExpressionList(const ExpressionList* newLastExpressionList);
  void UpdateLastExpressionList(
      std::unique_ptr<const ExpressionList> newLastExpressionList);

  void UpdateLastStatement(const Statement* newLastStatement);
  void UpdateLastStatement(std::unique_ptr<const Statement> newLastStatement);

  void UpdateLastStatementList(const StatementList* newLastStatementList);
  void UpdateLastStatementList(
      std::unique_ptr<const StatementList> newLastStatementList);

  std::unique_ptr<const Expression> CanonizeExpressionSubtree(
      std::unique_ptr<const Expression> expression) const;
  std::unique_ptr<const Statement> CanonizeStatementSubtree(
      std::unique_ptr<const Statement> statement) const;

  bool AreCommuting(const Statement* statement, const Expression* expression);
  const EseqExpression* CastToEseqExpression(const Expression* expression);

  std::unique_ptr<const Expression> lastExpression_;
  std::unique_ptr<const Statement> lastStatement_;
  std::unique_ptr<const ExpressionList> lastExpressionList_;
  std::unique_ptr<const StatementList> lastStatementList_;
};

std::unique_ptr<const Statement> EseqEliminationVisitor::ResultTree() {
  return std::move(ResultStatementTree());
}

std::unique_ptr<const Statement> EseqEliminationVisitor::ResultStatementTree() {
  return std::move(lastStatement_);
}

std::unique_ptr<const Expression>
EseqEliminationVisitor::ResultExpressionTree() {
  return std::move(lastExpression_);
}

void EseqEliminationVisitor::UpdateLastExpression(
    const Expression* newLastExpression) {
  lastExpression_ = std::unique_ptr<const Expression>(newLastExpression);
}

void EseqEliminationVisitor::UpdateLastExpression(
    std::unique_ptr<const Expression> newLastExpression) {
  lastExpression_ = std::move(newLastExpression);
}

void EseqEliminationVisitor::UpdateLastExpressionList(
    const ExpressionList* newLastExpressionList) {
  lastExpressionList_ =
      std::unique_ptr<const ExpressionList>(newLastExpressionList);
}

void EseqEliminationVisitor::UpdateLastExpressionList(
    std::unique_ptr<const ExpressionList> newLastExpressionList) {
  lastExpressionList_ = std::move(newLastExpressionList);
}

void EseqEliminationVisitor::UpdateLastStatement(
    const Statement* newLastStatement) {
  lastStatement_ = std::unique_ptr<const Statement>(newLastStatement);
}

void EseqEliminationVisitor::UpdateLastStatement(
    std::unique_ptr<const Statement> newLastStatement) {
  lastStatement_ = std::move(newLastStatement);
}

void EseqEliminationVisitor::UpdateLastStatementList(
    const StatementList* newLastStatementList) {
  lastStatementList_ =
      std::unique_ptr<const StatementList>(newLastStatementList);
}

void EseqEliminationVisitor::UpdateLastStatementList(
    std::unique_ptr<const StatementList> newLastStatementList) {
  lastStatementList_ = std::move(newLastStatementList);
}

std::unique_ptr<const Expression>
EseqEliminationVisitor::CanonizeExpressionSubtree(
    std::unique_ptr<const Expression> expression) const {
  EseqEliminationVisitor visitor(verbose_);
  expression->Accept(&visitor);
  return std::move(visitor.ResultExpressionTree());
}

std::unique_ptr<const Statement>
EseqEliminationVisitor::CanonizeStatementSubtree(
    std::unique_ptr<const Statement> statement) const {
  EseqEliminationVisitor visitor(verbose_);
  statement->Accept(&visitor);
  return std::move(visitor.ResultStatementTree());
}

bool EseqEliminationVisitor::AreCommuting(const Statement* statement,
                                          const Expression* expression) {
  assert(statement != nullptr && expression != nullptr);
  const ExpStatement* expStatement =
      dynamic_cast<const ExpStatement*>(statement);
  bool isStatementEmpty =
      expStatement != 0 &&
      dynamic_cast<const ConstExpression*>(expStatement->GetExpression()) != 0;
  return isStatementEmpty ||
         dynamic_cast<const ConstExpression*>(expression) != 0 ||
         dynamic_cast<const NameExpression*>(expression) != 0;
}

const EseqExpression* EseqEliminationVisitor::CastToEseqExpression(
    const Expression* expression) {
  return dynamic_cast<const EseqExpression*>(expression);
}

/*__________ Expressions __________*/

void EseqEliminationVisitor::Visit(const ConstExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expConst_);
  OnNodeEnter(nodeName);

  UpdateLastExpression(std::move(expression->Clone()));

  OnNodeExit(nodeName);
}

void EseqEliminationVisitor::Visit(const NameExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expName_);
  OnNodeEnter(nodeName);

  UpdateLastExpression(std::move(expression->Clone()));

  OnNodeExit(nodeName);
}

void EseqEliminationVisitor::Visit(const TempExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expTemp_);
  OnNodeEnter(nodeName);

  UpdateLastExpression(std::move(expression->Clone()));

  OnNodeExit(nodeName);
}

void EseqEliminationVisitor::Visit(const BinaryExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expBinary_);
  OnNodeEnter(nodeName);

  expression->LeftOperand()->Accept(this);
  std::unique_ptr<const Expression> leftOperandCanonized =
      std::move(lastExpression_);
  expression->RightOperand()->Accept(this);
  std::unique_ptr<const Expression> rightOperandCanonized =
      std::move(lastExpression_);

  const EseqExpression* leftOperandEseq =
      CastToEseqExpression(leftOperandCanonized.get());
  const EseqExpression* rightOperandEseq =
      CastToEseqExpression(rightOperandCanonized.get());

  std::unique_ptr<const Expression> resultExpression;

  if (leftOperandEseq != nullptr) {
    resultExpression =
        std::move(std::unique_ptr<const Expression>(new EseqExpression(
            std::move(leftOperandEseq->GetStatement()->Clone()),
            std::move(std::unique_ptr<const Expression>(new BinaryExpression(
                expression->Operation(),
                std::move(leftOperandEseq->GetExpression()->Clone()),
                std::move(rightOperandCanonized)))))));
    if (rightOperandEseq != nullptr) {
      resultExpression = CanonizeExpressionSubtree(std::move(resultExpression));
    }
  } else if (rightOperandEseq != nullptr) {
    if (AreCommuting(rightOperandEseq->GetStatement(),
                     leftOperandCanonized.get())) {
      resultExpression =
          std::move(std::unique_ptr<const Expression>(new EseqExpression(
              std::move(rightOperandEseq->GetStatement()->Clone()),
              std::move(std::unique_ptr<const Expression>(new BinaryExpression(
                  expression->Operation(), std::move(leftOperandCanonized),
                  std::move(rightOperandEseq->GetExpression()->Clone())))))));
    } else {
      Storage temp;
      resultExpression = std::move(std::unique_ptr<
                                   const Expression>(new EseqExpression(
          new MoveStatement(std::move(std::unique_ptr<const Expression>(
                                new TempExpression(temp))),
                            std::move(leftOperandCanonized)),
          new EseqExpression(
              std::move(rightOperandEseq->GetStatement()->Clone()),
              std::move(std::unique_ptr<const Expression>(new BinaryExpression(
                  expression->Operation(),
                  std::move(std::unique_ptr<const Expression>(
                      new TempExpression(temp))),
                  std::move(rightOperandEseq->GetExpression()->Clone()))))))));
      resultExpression =
          std::move(CanonizeExpressionSubtree(std::move(resultExpression)));
    }
  } else {
    resultExpression =
        std::move(std::unique_ptr<const Expression>(new BinaryExpression(
            expression->Operation(), std::move(leftOperandCanonized),
            std::move(rightOperandCanonized))));
  }

  UpdateLastExpression(std::move(resultExpression));

  OnNodeExit(nodeName);
}

void EseqEliminationVisitor::Visit(const MemExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expMem_);
  OnNodeEnter(nodeName);

  expression->Address()->Accept(this);
  std::unique_ptr<const Expression> addressCanonized =
      std::move(lastExpression_);

  const EseqExpression* addressEseq =
      CastToEseqExpression(addressCanonized.get());

  std::unique_ptr<const Expression> resultExpression = nullptr;
  if (addressEseq != nullptr) {
    resultExpression =
        std::move(std::unique_ptr<const Expression>(new EseqExpression(
            std::move(addressEseq->GetStatement()->Clone()),
            std::move(std::unique_ptr<const Expression>(new MemExpression(
                std::move(addressEseq->GetExpression()->Clone())))))));
  } else {
    resultExpression = std::move(std::unique_ptr<const Expression>(
        new MemExpression(std::move(addressCanonized))));
  }
  UpdateLastExpression(std::move(resultExpression));

  OnNodeExit(nodeName);
}

void EseqEliminationVisitor::Visit(const CallExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expCall_);
  OnNodeEnter(nodeName);

  expression->Function()->Accept(this);
  std::unique_ptr<const Expression> functionCanonized =
      std::move(lastExpression_);
  expression->Arguments()->Accept(this);
  std::unique_ptr<const ExpressionList> argumentsListCanonized =
      std::move(lastExpressionList_);

  std::vector<std::unique_ptr<const Statement>> newStatements;
  ExpressionList* tempExpressionList = new ExpressionList();

  const std::vector<std::unique_ptr<const Expression>>& argumentsCanonized =
      argumentsListCanonized->Expressions();
  for (auto it = argumentsCanonized.begin(); it != argumentsCanonized.end();
       ++it) {
    const EseqExpression* argumentEseq = CastToEseqExpression((*it).get());
    if (argumentEseq != nullptr) {
      newStatements.push_back(std::move(argumentEseq->GetStatement()->Clone()));
    }

    Storage temp;
    tempExpressionList->Add(new TempExpression(temp));

    std::unique_ptr<const Expression> moveSourceExpression;
    if (argumentEseq != nullptr) {
      moveSourceExpression = std::move(argumentEseq->GetExpression()->Clone());
    } else {
      moveSourceExpression = std::move((*it)->Clone());
    }
    std::unique_ptr<const Statement> moveStatement =
        std::move(std::unique_ptr<const Statement>(new MoveStatement(
            std::move(
                std::unique_ptr<const Expression>(new TempExpression(temp))),
            std::move(moveSourceExpression))));
    newStatements.push_back(std::move(moveStatement));
  }

  std::unique_ptr<const Expression> resultExpression;
  if (!newStatements.empty()) {
    std::unique_ptr<const Statement> suffixStatement =
        std::move(newStatements.back());
    newStatements.pop_back();
    for (auto it = newStatements.begin(); it != newStatements.end(); ++it) {
      suffixStatement = std::move(std::unique_ptr<const Statement>(
          new SeqStatement(std::move(*it), std::move(suffixStatement))));
    }

    resultExpression =
        std::move(std::unique_ptr<const Expression>(new EseqExpression(
            std::move(suffixStatement),
            std::move(std::unique_ptr<const Expression>(new CallExpression(
                std::move(functionCanonized),
                std::move(std::unique_ptr<const ExpressionList>(
                    tempExpressionList))))))));
  } else {
    resultExpression =
        std::move(std::unique_ptr<const Expression>(new CallExpression(
            std::move(functionCanonized), std::move(argumentsListCanonized))));
  }

  UpdateLastExpression(std::move(resultExpression));

  OnNodeExit(nodeName);
}

void EseqEliminationVisitor::Visit(const EseqExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expEseq_);
  OnNodeEnter(nodeName);

  expression->GetStatement()->Accept(this);
  std::unique_ptr<const Statement> statementCanonized =
      std::move(lastStatement_);
  expression->GetExpression()->Accept(this);
  std::unique_ptr<const Expression> expressionCanonized =
      std::move(lastExpression_);

  const EseqExpression* eseqExpression =
      CastToEseqExpression(expressionCanonized.get());
  std::unique_ptr<const Expression> resultExpression;
  if (eseqExpression != nullptr) {
    resultExpression =
        std::move(std::unique_ptr<const Expression>(new EseqExpression(
            std::move(std::unique_ptr<const Statement>(new SeqStatement(
                std::move(statementCanonized),
                std::move(eseqExpression->GetStatement()->Clone())))),
            std::move(eseqExpression->GetExpression()->Clone()))));
  } else {
    resultExpression =
        std::move(std::unique_ptr<const Expression>(new EseqExpression(
            std::move(statementCanonized), std::move(expressionCanonized))));
  }

  UpdateLastExpression(std::move(resultExpression));

  OnNodeExit(nodeName);
}

/*__________ Statements __________*/

void EseqEliminationVisitor::Visit(const ExpStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statExp_);
  OnNodeEnter(nodeName);

  statement->GetExpression()->Accept(this);
  std::unique_ptr<const Expression> expressionCanonized =
      std::move(lastExpression_);

  const EseqExpression* eseqExpression =
      CastToEseqExpression(expressionCanonized.get());
  std::unique_ptr<const Statement> resultStatement;
  if (eseqExpression != nullptr) {
    resultStatement =
        std::move(std::unique_ptr<const Statement>(new SeqStatement(
            std::move(eseqExpression->GetStatement()->Clone()),
            std::move(std::unique_ptr<const Statement>(new ExpStatement(
                std::move(eseqExpression->GetExpression()->Clone())))))));
  } else {
    resultStatement = std::move(std::unique_ptr<const Statement>(
        new ExpStatement(std::move(expressionCanonized))));
  }

  UpdateLastStatement(std::move(resultStatement));

  OnNodeExit(nodeName);
}

void EseqEliminationVisitor::Visit(const JumpConditionalStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statCJump_);
  OnNodeEnter(nodeName);

  statement->LeftOperand()->Accept(this);
  std::unique_ptr<const Expression> leftOperandCanonized =
      std::move(lastExpression_);
  statement->RightOperand()->Accept(this);
  std::unique_ptr<const Expression> rightOperandCanonized =
      std::move(lastExpression_);

  const EseqExpression* leftOperandEseq =
      CastToEseqExpression(leftOperandCanonized.get());
  const EseqExpression* rightOperandEseq =
      CastToEseqExpression(rightOperandCanonized.get());

  std::unique_ptr<const Statement> resultStatement;

  if (leftOperandEseq != nullptr) {
    resultStatement =
        std::move(std::unique_ptr<const Statement>(new JumpConditionalStatement(
            statement->Operation(),
            std::move(leftOperandEseq->GetExpression()->Clone()),
            std::move(rightOperandCanonized), statement->TrueLabel(),
            statement->FalseLabel())));
    if (rightOperandEseq != nullptr) {
      resultStatement =
          std::move(CanonizeStatementSubtree(std::move(resultStatement)));
    }

    resultStatement = std::move(std::unique_ptr<const Statement>(
        new SeqStatement(std::move(leftOperandEseq->GetStatement()->Clone()),
                         std::move(resultStatement))));
  } else if (rightOperandEseq != nullptr) {
    if (AreCommuting(rightOperandEseq->GetStatement(),
                     leftOperandCanonized.get())) {
      resultStatement =
          std::move(std::unique_ptr<const Statement>(new SeqStatement(
              std::move(rightOperandEseq->GetStatement()->Clone()),
              std::move(
                  std::unique_ptr<const Statement>(new JumpConditionalStatement(
                      statement->Operation(), std::move(leftOperandCanonized),
                      std::move(rightOperandEseq->GetExpression()->Clone()),
                      statement->TrueLabel(), statement->FalseLabel()))))));
    } else {
      Storage temp;
      resultStatement =
          std::move(std::unique_ptr<const Statement>(new SeqStatement(
              new MoveStatement(std::move(std::unique_ptr<const Expression>(
                                    new TempExpression(temp))),
                                std::move(leftOperandCanonized)),
              new SeqStatement(
                  std::move(rightOperandEseq->GetStatement()->Clone()),
                  std::move(std::unique_ptr<const Statement>(
                      new JumpConditionalStatement(
                          statement->Operation(),
                          std::move(std::unique_ptr<const Expression>(
                              new TempExpression(temp))),
                          std::move(rightOperandEseq->GetExpression()->Clone()),
                          statement->TrueLabel(),
                          statement->FalseLabel())))))));
    }
  } else {
    resultStatement =
        std::move(std::unique_ptr<const Statement>(new JumpConditionalStatement(
            statement->Operation(), std::move(leftOperandCanonized),
            std::move(rightOperandCanonized), statement->TrueLabel(),
            statement->FalseLabel())));
  }

  UpdateLastStatement(std::move(resultStatement));

  OnNodeExit(nodeName);
}

void EseqEliminationVisitor::Visit(const JumpStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statJump_);
  OnNodeEnter(nodeName);

  UpdateLastStatement(std::move(statement->Clone()));

  OnNodeExit(nodeName);
}

void EseqEliminationVisitor::Visit(const LabelStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statLabel_);
  OnNodeEnter(nodeName);

  UpdateLastStatement(std::move(statement->Clone()));

  OnNodeExit(nodeName);
}

void EseqEliminationVisitor::Visit(const MoveStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statMove_);
  OnNodeEnter(nodeName);

  statement->Destination()->Accept(this);
  std::unique_ptr<const Expression> destinationCanonized =
      std::move(lastExpression_);
  statement->Source()->Accept(this);
  std::unique_ptr<const Expression> sourceCanonized =
      std::move(lastExpression_);

  const EseqExpression* destinationEseq =
      CastToEseqExpression(destinationCanonized.get());
  const EseqExpression* sourceEseq =
      CastToEseqExpression(sourceCanonized.get());

  std::unique_ptr<const Statement> resultStatement;
  if (destinationEseq != nullptr) {
    // left son is eseq
    resultStatement = std::move(std::unique_ptr<const Statement>(
        new MoveStatement(std::move(destinationEseq->GetExpression()->Clone()),
                          std::move(sourceCanonized))));
    if (sourceEseq != nullptr) {
      // right son is eseq
      resultStatement =
          std::move(CanonizeStatementSubtree(std::move(resultStatement)));
    }
    resultStatement = std::move(std::unique_ptr<const Statement>(
        new SeqStatement(std::move(destinationEseq->GetStatement()->Clone()),
                         std::move(resultStatement))));
  } else if (sourceEseq != nullptr) {
    // right son is eseq
    if (AreCommuting(sourceEseq->GetStatement(), destinationCanonized.get())) {
      resultStatement =
          std::move(std::unique_ptr<const Statement>(new SeqStatement(
              std::move(sourceEseq->GetStatement()->Clone()),
              std::move(std::unique_ptr<const Statement>(new MoveStatement(
                  std::move(destinationCanonized),
                  std::move(sourceEseq->GetExpression()->Clone())))))));
    } else {
      Storage temp;
      resultStatement =
          std::move(std::unique_ptr<const Statement>(new SeqStatement(
              new MoveStatement(std::move(std::unique_ptr<const Expression>(
                                    new TempExpression(temp))),
                                std::move(destinationCanonized)),
              new SeqStatement(
                  std::move(sourceEseq->GetStatement()->Clone()),
                  std::move(std::unique_ptr<const Statement>(new MoveStatement(
                      std::move(std::unique_ptr<const Expression>(
                          new TempExpression(temp))),
                      std::move(sourceEseq->GetExpression()->Clone()))))))));
    }
  } else {
    resultStatement =
        std::move(std::unique_ptr<const Statement>(new MoveStatement(
            std::move(destinationCanonized), std::move(sourceCanonized))));
  }

  UpdateLastStatement(std::move(resultStatement));

  OnNodeExit(nodeName);
}

void EseqEliminationVisitor::Visit(const SeqStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statSeq_);
  OnNodeEnter(nodeName);

  statement->LeftStatement()->Accept(this);
  std::unique_ptr<const Statement> leftStatementCanonized =
      std::move(lastStatement_);
  statement->RightStatement()->Accept(this);
  std::unique_ptr<const Statement> rightStatementCanonized =
      std::move(lastStatement_);

  UpdateLastStatement(new SeqStatement(std::move(leftStatementCanonized),
                                       std::move(rightStatementCanonized)));

  OnNodeExit(nodeName);
}

/*__________  Lists __________*/

void EseqEliminationVisitor::Visit(const ExpressionList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::listExp_);
  OnNodeEnter(nodeName);

  ExpressionList* newList = new ExpressionList();
  const std::vector<std::unique_ptr<const Expression>>& expressions =
      list->Expressions();
  for (auto it = expressions.begin(); it != expressions.end(); ++it) {
    (*it)->Accept(this);
    newList->Add(std::move(lastExpression_));
  }

  UpdateLastExpressionList(newList);

  OnNodeExit(nodeName);
}

void EseqEliminationVisitor::Visit(const StatementList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::listStat_);
  OnNodeEnter(nodeName);

  // such calls should never happen
  assert(false);

  OnNodeExit(nodeName);
}

}  // namespace Irt
