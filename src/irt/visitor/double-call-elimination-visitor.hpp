#pragma once

#include <irt/node/node-names.hpp>
#include <irt/visitor/visitor.hpp>

#include <irt/node/expression-list.hpp>
#include <irt/node/expression.hpp>
#include <irt/node/statement.hpp>

namespace Irt {

class DoubleCallEliminationVisitor : public Visitor {
 public:
  DoubleCallEliminationVisitor(bool verbose = false) : Visitor(verbose) {}
  ~DoubleCallEliminationVisitor() {}

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

  void UpdateLastExpressionList(const ExpressionList* newLastExpressionList);
  void UpdateLastExpressionList(
      std::unique_ptr<const ExpressionList> newLastExpressionList);

  void UpdateLastStatement(const Statement* newLastStatement);
  void UpdateLastStatement(std::unique_ptr<const Statement> newLastStatement);

  void UpdateLastStatementList(const StatementList* newLastStatementList);
  void UpdateLastStatementList(
      std::unique_ptr<const StatementList> newLastStatementList);

  std::unique_ptr<const Expression> lastExpression_;
  std::unique_ptr<const Statement> lastStatement_;
  std::unique_ptr<const ExpressionList> lastExpressionList_;
  std::unique_ptr<const StatementList> lastStatementList_;
};

std::unique_ptr<const Statement> DoubleCallEliminationVisitor::ResultTree() {
  return std::move(lastStatement_);
}

void DoubleCallEliminationVisitor::UpdateLastExpression(
    const Expression* newLastExpression) {
  lastExpression_ = std::unique_ptr<const Expression>(newLastExpression);
}

void DoubleCallEliminationVisitor::UpdateLastExpression(
    std::unique_ptr<const Expression> newLastExpression) {
  lastExpression_ = std::move(newLastExpression);
}

void DoubleCallEliminationVisitor::UpdateLastExpressionList(
    const ExpressionList* newLastExpressionList) {
  lastExpressionList_ =
      std::unique_ptr<const ExpressionList>(newLastExpressionList);
}

void DoubleCallEliminationVisitor::UpdateLastExpressionList(
    std::unique_ptr<const ExpressionList> newLastExpressionList) {
  lastExpressionList_ = std::move(newLastExpressionList);
}

void DoubleCallEliminationVisitor::UpdateLastStatement(
    const Statement* newLastStatement) {
  lastStatement_ = std::unique_ptr<const Statement>(newLastStatement);
}

void DoubleCallEliminationVisitor::UpdateLastStatement(
    std::unique_ptr<const Statement> newLastStatement) {
  lastStatement_ = std::move(newLastStatement);
}

void DoubleCallEliminationVisitor::UpdateLastStatementList(
    const StatementList* newLastStatementList) {
  lastStatementList_ =
      std::unique_ptr<const StatementList>(newLastStatementList);
}

void DoubleCallEliminationVisitor::UpdateLastStatementList(
    std::unique_ptr<const StatementList> newLastStatementList) {
  lastStatementList_ = std::move(newLastStatementList);
}

/*__________ Expressions __________*/

void DoubleCallEliminationVisitor::Visit(const ConstExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expConst_);
  OnNodeEnter(nodeName);

  UpdateLastExpression(new ConstExpression(expression->Value()));

  OnNodeExit(nodeName);
}

void DoubleCallEliminationVisitor::Visit(const NameExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expName_);
  OnNodeEnter(nodeName);

  UpdateLastExpression(new NameExpression(expression->GetAddress()));

  OnNodeExit(nodeName);
}

void DoubleCallEliminationVisitor::Visit(const TempExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expTemp_);
  OnNodeEnter(nodeName);

  UpdateLastExpression(new TempExpression(expression->GetStorage()));

  OnNodeExit(nodeName);
}

void DoubleCallEliminationVisitor::Visit(const BinaryExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expBinary_);
  OnNodeEnter(nodeName);

  expression->LeftOperand()->Accept(this);
  std::unique_ptr<const Expression> expressionLeft = std::move(lastExpression_);

  expression->RightOperand()->Accept(this);
  std::unique_ptr<const Expression> expressionRight =
      std::move(lastExpression_);

  UpdateLastExpression(new BinaryExpression(expression->Operation(),
                                            std::move(expressionLeft),
                                            std::move(expressionRight)));

  OnNodeExit(nodeName);
}

void DoubleCallEliminationVisitor::Visit(const MemExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expMem_);
  OnNodeEnter(nodeName);

  expression->Address()->Accept(this);
  std::unique_ptr<const Expression> addressExpression =
      std::move(lastExpression_);

  UpdateLastExpression(new MemExpression(std::move(addressExpression)));

  OnNodeExit(nodeName);
}

void DoubleCallEliminationVisitor::Visit(const CallExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expCall_);
  OnNodeEnter(nodeName);

  expression->Function()->Accept(this);
  std::unique_ptr<const Expression> functionExpression =
      std::move(lastExpression_);
  expression->Arguments()->Accept(this);
  std::unique_ptr<const ExpressionList> argumentsList =
      std::move(lastExpressionList_);

  Storage temp;
  UpdateLastExpression(new EseqExpression(
      new MoveStatement(new TempExpression(temp),
                        new CallExpression(std::move(functionExpression),
                                           std::move(argumentsList))),
      new TempExpression(temp)));

  OnNodeExit(nodeName);
}

void DoubleCallEliminationVisitor::Visit(const EseqExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expEseq_);
  OnNodeEnter(nodeName);

  expression->GetStatement()->Accept(this);
  expression->GetExpression()->Accept(this);

  UpdateLastExpression(new EseqExpression(std::move(lastStatement_),
                                          std::move(lastExpression_)));

  OnNodeExit(nodeName);
}

/*__________ Statements __________*/

void DoubleCallEliminationVisitor::Visit(const ExpStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statExp_);
  OnNodeEnter(nodeName);

  statement->GetExpression()->Accept(this);
  std::unique_ptr<const Expression> expression = std::move(lastExpression_);

  UpdateLastStatement(new ExpStatement(std::move(expression)));

  OnNodeExit(nodeName);
}

void DoubleCallEliminationVisitor::Visit(
    const JumpConditionalStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statCJump_);
  OnNodeEnter(nodeName);

  statement->LeftOperand()->Accept(this);
  std::unique_ptr<const Expression> expressionLeft = std::move(lastExpression_);

  statement->RightOperand()->Accept(this);
  std::unique_ptr<const Expression> expressionRight =
      std::move(lastExpression_);

  UpdateLastStatement(new JumpConditionalStatement(
      statement->Operation(), std::move(expressionLeft),
      std::move(expressionRight), statement->TrueLabel(),
      statement->FalseLabel()));

  OnNodeExit(nodeName);
}

void DoubleCallEliminationVisitor::Visit(const JumpStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statJump_);
  OnNodeEnter(nodeName);

  UpdateLastStatement(new JumpStatement(statement->Target()));

  OnNodeExit(nodeName);
}

void DoubleCallEliminationVisitor::Visit(const LabelStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statLabel_);
  OnNodeEnter(nodeName);

  UpdateLastStatement(new LabelStatement(statement->Label()));

  OnNodeExit(nodeName);
}

void DoubleCallEliminationVisitor::Visit(const MoveStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statMove_);
  OnNodeEnter(nodeName);

  statement->Destination()->Accept(this);
  std::unique_ptr<const Expression> destination = std::move(lastExpression_);

  statement->Source()->Accept(this);
  std::unique_ptr<const Expression> source = std::move(lastExpression_);

  UpdateLastStatement(
      new MoveStatement(std::move(destination), std::move(source)));

  OnNodeExit(nodeName);
}

void DoubleCallEliminationVisitor::Visit(const SeqStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statSeq_);
  OnNodeEnter(nodeName);

  statement->LeftStatement()->Accept(this);
  std::unique_ptr<const Statement> statementLeft = std::move(lastStatement_);

  statement->RightStatement()->Accept(this);
  std::unique_ptr<const Statement> statementRight = std::move(lastStatement_);

  UpdateLastStatement(
      new SeqStatement(std::move(statementLeft), std::move(statementRight)));

  OnNodeExit(nodeName);
}

/*__________  Lists __________*/

void DoubleCallEliminationVisitor::Visit(const ExpressionList* list) {
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

void DoubleCallEliminationVisitor::Visit(const StatementList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::listStat_);
  OnNodeEnter(nodeName);

  StatementList* newList = new StatementList();

  const std::vector<std::unique_ptr<const Statement>>& statements =
      list->Statements();
  for (auto it = statements.begin(); it != statements.end(); ++it) {
    (*it)->Accept(this);
    newList->Add(std::move(lastStatement_));
  }

  UpdateLastStatementList(newList);

  OnNodeExit(nodeName);
}

}  // namespace Irt
