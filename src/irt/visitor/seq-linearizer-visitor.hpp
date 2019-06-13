#pragma once

#include <cassert>
#include <deque>
#include <limits>
#include <vector>

#include <irt/node/node-names.hpp>
#include <irt/visitor/visitor.hpp>

#include <irt/node/expression-list.hpp>
#include <irt/node/expression.hpp>
#include <irt/node/statement.hpp>

namespace Irt {

class SeqLinearizerVisitor : public Visitor {
 public:
  SeqLinearizerVisitor(bool verbose = false)
      : Visitor(verbose),
        distanceToSeqStack_(1, std::numeric_limits<int>::max() - 1) {}
  ~SeqLinearizerVisitor() {}

  std::unique_ptr<const Statement> ResultTree();

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

  void UpdateLastStatement(const Statement* newLastStatement);
  void UpdateLastStatement(std::unique_ptr<const Statement> newLastStatement);

  void UpdateLastExpressionList(const ExpressionList* newLastExpressionList);
  void UpdateLastExpressionList(
      std::unique_ptr<const ExpressionList> newLastExpressionList);

  void SaveResult(std::unique_ptr<const Statement> result);

  std::vector<std::unique_ptr<std::vector<std::unique_ptr<const Statement>>>>
      statementStack_;  // stack of statements
  std::vector<int> distanceToSeqStack_;
  std::unique_ptr<const Statement> lastStatement_;
  std::unique_ptr<const Expression> lastExpression_;
  std::unique_ptr<const ExpressionList> lastExpressionList_;
};

std::unique_ptr<const Statement> SeqLinearizerVisitor::ResultTree() {
  return std::move(lastStatement_);
}

void SeqLinearizerVisitor::UpdateLastExpression(
    const Expression* newLastExpression) {
  lastExpression_ = std::unique_ptr<const Expression>(newLastExpression);
}

void SeqLinearizerVisitor::UpdateLastExpression(
    std::unique_ptr<const Expression> newLastExpression) {
  lastExpression_ = std::move(newLastExpression);
}

void SeqLinearizerVisitor::UpdateLastStatement(
    const Statement* newLastStatement) {
  lastStatement_ = std::unique_ptr<const Statement>(newLastStatement);
}

void SeqLinearizerVisitor::UpdateLastStatement(
    std::unique_ptr<const Statement> newLastStatement) {
  lastStatement_ = std::move(newLastStatement);
}

void SeqLinearizerVisitor::UpdateLastExpressionList(
    const ExpressionList* newLastExpressionList) {
  lastExpressionList_ =
      std::unique_ptr<const ExpressionList>(newLastExpressionList);
}

void SeqLinearizerVisitor::UpdateLastExpressionList(
    std::unique_ptr<const ExpressionList> newLastExpressionList) {
  lastExpressionList_ = std::move(newLastExpressionList);
}

void SeqLinearizerVisitor::SaveResult(std::unique_ptr<const Statement> result) {
  if (distanceToSeqStack_.back() == 1) {
    statementStack_.back()->push_back(std::move(result));
  } else {
    UpdateLastStatement(std::move(result));
  }
}

/*__________ Expressions __________*/

void SeqLinearizerVisitor::Visit(const ConstExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expConst_);
  OnNodeEnter(nodeName);

  ++distanceToSeqStack_.back();

  UpdateLastExpression(std::move(expression->Clone()));

  --distanceToSeqStack_.back();

  OnNodeExit(nodeName);
}

void SeqLinearizerVisitor::Visit(const NameExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expName_);
  OnNodeEnter(nodeName);

  ++distanceToSeqStack_.back();

  UpdateLastExpression(std::move(expression->Clone()));

  --distanceToSeqStack_.back();

  OnNodeExit(nodeName);
}

void SeqLinearizerVisitor::Visit(const TempExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expTemp_);
  OnNodeEnter(nodeName);

  ++distanceToSeqStack_.back();

  UpdateLastExpression(std::move(expression->Clone()));

  --distanceToSeqStack_.back();

  OnNodeExit(nodeName);
}

void SeqLinearizerVisitor::Visit(const BinaryExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expBinary_);
  OnNodeEnter(nodeName);

  ++distanceToSeqStack_.back();

  expression->LeftOperand()->Accept(this);
  std::unique_ptr<const Expression> leftOperand = std::move(lastExpression_);
  expression->RightOperand()->Accept(this);
  std::unique_ptr<const Expression> rightOperand = std::move(lastExpression_);

  UpdateLastExpression(new BinaryExpression(expression->Operation(),
                                            std::move(leftOperand),
                                            std::move(rightOperand)));

  --distanceToSeqStack_.back();

  OnNodeExit(nodeName);
}

void SeqLinearizerVisitor::Visit(const MemExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expMem_);
  OnNodeEnter(nodeName);

  ++distanceToSeqStack_.back();

  expression->Address()->Accept(this);
  std::unique_ptr<const Expression> addressExpression =
      std::move(lastExpression_);

  UpdateLastExpression(new MemExpression(std::move(addressExpression)));

  --distanceToSeqStack_.back();

  OnNodeExit(nodeName);
}

void SeqLinearizerVisitor::Visit(const CallExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expCall_);
  OnNodeEnter(nodeName);

  ++distanceToSeqStack_.back();

  expression->Function()->Accept(this);
  std::unique_ptr<const Expression> functionExpression =
      std::move(lastExpression_);
  expression->Arguments()->Accept(this);
  std::unique_ptr<const ExpressionList> argumentList =
      std::move(lastExpressionList_);

  UpdateLastExpression(new CallExpression(std::move(functionExpression),
                                          std::move(argumentList)));

  --distanceToSeqStack_.back();

  OnNodeExit(nodeName);
}

void SeqLinearizerVisitor::Visit(const EseqExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expEseq_);
  OnNodeEnter(nodeName);

  // such calls should never happen
  assert(false);

  OnNodeExit(nodeName);
}

/*__________ Statements __________*/

void SeqLinearizerVisitor::Visit(const ExpStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statExp_);
  OnNodeEnter(nodeName);

  ++distanceToSeqStack_.back();

  statement->GetExpression()->Accept(this);
  std::unique_ptr<const Expression> expression = std::move(lastExpression_);

  std::unique_ptr<Statement> result(new ExpStatement(std::move(expression)));
  SaveResult(std::move(result));

  --distanceToSeqStack_.back();

  OnNodeExit(nodeName);
}

void SeqLinearizerVisitor::Visit(const JumpConditionalStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statCJump_);
  OnNodeEnter(nodeName);

  ++distanceToSeqStack_.back();

  statement->LeftOperand()->Accept(this);
  std::unique_ptr<const Expression> leftOperand = std::move(lastExpression_);
  statement->RightOperand()->Accept(this);
  std::unique_ptr<const Expression> rightOperand = std::move(lastExpression_);

  std::unique_ptr<Statement> result(new JumpConditionalStatement(
      statement->Operation(), std::move(leftOperand), std::move(rightOperand),
      statement->TrueLabel(), statement->FalseLabel()));
  SaveResult(std::move(result));

  --distanceToSeqStack_.back();

  OnNodeExit(nodeName);
}

void SeqLinearizerVisitor::Visit(const JumpStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statJump_);
  OnNodeEnter(nodeName);

  ++distanceToSeqStack_.back();

  std::unique_ptr<Statement> result(new JumpStatement(statement->Target()));
  SaveResult(std::move(result));

  --distanceToSeqStack_.back();

  OnNodeExit(nodeName);
}

void SeqLinearizerVisitor::Visit(const LabelStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statLabel_);
  OnNodeEnter(nodeName);

  ++distanceToSeqStack_.back();

  std::unique_ptr<Statement> result(new LabelStatement(statement->Label()));
  SaveResult(std::move(result));

  --distanceToSeqStack_.back();

  OnNodeExit(nodeName);
}

void SeqLinearizerVisitor::Visit(const MoveStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statMove_);
  OnNodeEnter(nodeName);

  ++distanceToSeqStack_.back();

  statement->Destination()->Accept(this);
  std::unique_ptr<const Expression> destination = std::move(lastExpression_);
  statement->Source()->Accept(this);
  std::unique_ptr<const Expression> source = std::move(lastExpression_);

  std::unique_ptr<Statement> result(
      new MoveStatement(std::move(destination), std::move(source)));
  SaveResult(std::move(result));

  --distanceToSeqStack_.back();

  OnNodeExit(nodeName);
}

void SeqLinearizerVisitor::Visit(const SeqStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statSeq_);
  OnNodeEnter(nodeName);

  ++distanceToSeqStack_.back();

  if (distanceToSeqStack_.back() > 1) {
    statementStack_.emplace_back(
        new std::vector<std::unique_ptr<const Statement>>());
  }

  distanceToSeqStack_.push_back(0);
  statement->LeftStatement()->Accept(this);
  statement->RightStatement()->Accept(this);

  distanceToSeqStack_.pop_back();
  if (distanceToSeqStack_.back() > 1) {
    StatementList* statementList = new StatementList();
    for (auto it = statementStack_.back()->begin();
         it != statementStack_.back()->end(); ++it) {
      statementList->Add(std::move(*it));
    }
    UpdateLastStatement(statementList);
    statementStack_.pop_back();
  }

  --distanceToSeqStack_.back();

  OnNodeExit(nodeName);
}

/*__________  Lists __________*/

void SeqLinearizerVisitor::Visit(const ExpressionList* list) {
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

void SeqLinearizerVisitor::Visit(const StatementList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::listStat_);
  OnNodeEnter(nodeName);

  // such calls should never happen
  assert(false);

  OnNodeExit(nodeName);
}

}  // namespace Irt
