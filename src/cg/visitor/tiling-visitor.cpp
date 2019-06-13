#include <cassert>
#include <cg/visitor/tiling-visitor.hpp>

using namespace Cg;

/*__________ Expressions __________*/

void TilingVisitor::Visit(const ConstExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expConst_);
  OnNodeEnter(nodeName);

  ApplyPatterns(expression);

  OnNodeExit(nodeName);
}

void TilingVisitor::Visit(const NameExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expName_);
  OnNodeEnter(nodeName);

  ApplyPatterns(expression);

  OnNodeExit(nodeName);
}

void TilingVisitor::Visit(const Irt::TempExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expTemp_);
  OnNodeEnter(nodeName);

  ApplyPatterns(expression);

  OnNodeExit(nodeName);
}

void TilingVisitor::Visit(const BinaryExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expBinary_);
  OnNodeEnter(nodeName);

  expression->LeftOperand()->Accept(this);
  expression->RightOperand()->Accept(this);

  ApplyPatterns(expression);

  OnNodeExit(nodeName);
}

void TilingVisitor::Visit(const MemExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expMem_);
  OnNodeEnter(nodeName);

  expression->Address()->Accept(this);

  ApplyPatterns(expression);

  OnNodeExit(nodeName);
}

void TilingVisitor::Visit(const CallExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expCall_);
  OnNodeEnter(nodeName);

  expression->Function()->Accept(this);
  expression->Arguments()->Accept(this);

  ApplyPatterns(expression);

  OnNodeExit(nodeName);
}

void TilingVisitor::Visit(const EseqExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expEseq_);
  OnNodeEnter(nodeName);

  assert(false);

  OnNodeExit(nodeName);
}

/*__________ Statements __________*/

void TilingVisitor::Visit(const ExpStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statExp_);
  OnNodeEnter(nodeName);

  statement->GetExpression()->Accept(this);

  ApplyPatterns(statement);

  OnNodeExit(nodeName);
}

void TilingVisitor::Visit(const JumpConditionalStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statCJump_);
  OnNodeEnter(nodeName);

  statement->LeftOperand()->Accept(this);
  statement->RightOperand()->Accept(this);

  ApplyPatterns(statement);

  OnNodeExit(nodeName);
}

void TilingVisitor::Visit(const JumpStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statJump_);
  OnNodeEnter(nodeName);

  ApplyPatterns(statement);

  OnNodeExit(nodeName);
}

void TilingVisitor::Visit(const LabelStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statLabel_);
  OnNodeEnter(nodeName);

  ApplyPatterns(statement);

  OnNodeExit(nodeName);
}

void TilingVisitor::Visit(const MoveStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statMove_);
  OnNodeEnter(nodeName);

  statement->Source()->Accept(this);
  statement->Destination()->Accept(this);

  ApplyPatterns(statement);

  OnNodeExit(nodeName);
}

void TilingVisitor::Visit(const SeqStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statSeq_);
  OnNodeEnter(nodeName);

  assert(false);

  OnNodeExit(nodeName);
}

/*__________  Lists __________*/

void TilingVisitor::Visit(const ExpressionList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::listExp_);
  OnNodeEnter(nodeName);

  for (const auto& expression : list->Expressions()) {
    expression->Accept(this);
  }

  ApplyPatterns(list);

  OnNodeExit(nodeName);
}

void TilingVisitor::Visit(const StatementList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::listStat_);
  OnNodeEnter(nodeName);

  assert(false);

  OnNodeExit(nodeName);
}
