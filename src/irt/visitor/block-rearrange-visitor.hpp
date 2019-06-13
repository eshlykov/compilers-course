#pragma once

#include <cassert>
#include <memory>
#include <string>

#include <irt/node/node-names.hpp>
#include <irt/visitor/visitor.hpp>

#include <irt/node/expression-list.hpp>
#include <irt/node/expression.hpp>
#include <irt/node/statement.hpp>

namespace Irt {

class BlockRearrangeVisitor : public Visitor {
 public:
  BlockRearrangeVisitor(bool verbose = false) : Visitor(verbose) {}
  ~BlockRearrangeVisitor() {}

  std::string LabelName() const;
  std::shared_ptr<std::string> JumpTargetLabelName() const;

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
  std::string labelName_;
  std::shared_ptr<std::string> jumpTargetLabelName_;
};

std::string BlockRearrangeVisitor::LabelName() const { return labelName_; }

std::shared_ptr<std::string> BlockRearrangeVisitor::JumpTargetLabelName()
    const {
  return jumpTargetLabelName_;
}

/*__________ Expressions __________*/

void BlockRearrangeVisitor::Visit(const ConstExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expConst_);
  OnNodeEnter(nodeName);

  assert(false);  // such calls should never happen

  OnNodeExit(nodeName);
}

void BlockRearrangeVisitor::Visit(const NameExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expName_);
  OnNodeEnter(nodeName);

  assert(false);  // such calls should never happen

  OnNodeExit(nodeName);
}

void BlockRearrangeVisitor::Visit(const TempExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expTemp_);
  OnNodeEnter(nodeName);

  assert(false);  // such calls should never happen

  OnNodeExit(nodeName);
}

void BlockRearrangeVisitor::Visit(const BinaryExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expBinary_);
  OnNodeEnter(nodeName);

  assert(false);  // such calls should never happen

  OnNodeExit(nodeName);
}

void BlockRearrangeVisitor::Visit(const MemExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expMem_);
  OnNodeEnter(nodeName);

  assert(false);  // such calls should never happen

  OnNodeExit(nodeName);
}

void BlockRearrangeVisitor::Visit(const CallExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expCall_);
  OnNodeEnter(nodeName);

  assert(false);  // such calls should never happen

  OnNodeExit(nodeName);
}

void BlockRearrangeVisitor::Visit(const EseqExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expEseq_);
  OnNodeEnter(nodeName);

  assert(false);  // such calls should never happen

  OnNodeExit(nodeName);
}

/*__________ Statements __________*/

void BlockRearrangeVisitor::Visit(const ExpStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statExp_);
  OnNodeEnter(nodeName);

  OnNodeExit(nodeName);
}

void BlockRearrangeVisitor::Visit(const JumpConditionalStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statCJump_);
  OnNodeEnter(nodeName);

  jumpTargetLabelName_ =
      std::make_shared<std::string>(statement->FalseLabel().ToString());

  OnNodeExit(nodeName);
}

void BlockRearrangeVisitor::Visit(const JumpStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statJump_);
  OnNodeEnter(nodeName);

  jumpTargetLabelName_ =
      std::make_shared<std::string>(statement->Target().ToString());

  OnNodeExit(nodeName);
}

void BlockRearrangeVisitor::Visit(const LabelStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statLabel_);
  OnNodeEnter(nodeName);

  labelName_ = statement->Label().ToString();

  OnNodeExit(nodeName);
}

void BlockRearrangeVisitor::Visit(const MoveStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statMove_);
  OnNodeEnter(nodeName);

  OnNodeExit(nodeName);
}

void BlockRearrangeVisitor::Visit(const SeqStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statSeq_);
  OnNodeEnter(nodeName);

  OnNodeExit(nodeName);
}

/*__________  Lists __________*/

void BlockRearrangeVisitor::Visit(const ExpressionList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::listExp_);
  OnNodeEnter(nodeName);

  assert(false);  // such calls should never happen

  OnNodeExit(nodeName);
}

void BlockRearrangeVisitor::Visit(const StatementList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::listStat_);
  OnNodeEnter(nodeName);

  list->Statements().front()->Accept(this);
  list->Statements().back()->Accept(this);

  OnNodeExit(nodeName);
}

}  // namespace Irt
