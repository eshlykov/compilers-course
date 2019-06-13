#include <irt/visitor/trace-formation-visitor.hpp>

#include <cassert>

#include <utils/address.hpp>

using namespace Irt;

std::unique_ptr<Cg::Trace> TraceFormationVisitor::Trace() {
  return std::move(trace_);
}

std::string TraceFormationVisitor::EndBlockLabelName() { return "epilogue"; }

/*__________ Expressions __________*/

void TraceFormationVisitor::Visit(const ConstExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expConst_);
  OnNodeEnter(nodeName);

  lastVisitedNodeType_ = NodeTypes::Other;

  OnNodeExit(nodeName);
}

void TraceFormationVisitor::Visit(const NameExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expName_);
  OnNodeEnter(nodeName);

  lastVisitedNodeType_ = NodeTypes::Other;

  OnNodeExit(nodeName);
}

void TraceFormationVisitor::Visit(const TempExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expTemp_);
  OnNodeEnter(nodeName);

  lastVisitedNodeType_ = NodeTypes::Other;

  OnNodeExit(nodeName);
}

void TraceFormationVisitor::Visit(const BinaryExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expBinary_);
  OnNodeEnter(nodeName);

  lastVisitedNodeType_ = NodeTypes::Other;

  OnNodeExit(nodeName);
}

void TraceFormationVisitor::Visit(const MemExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expMem_);
  OnNodeEnter(nodeName);

  lastVisitedNodeType_ = NodeTypes::Other;

  OnNodeExit(nodeName);
}

void TraceFormationVisitor::Visit(const CallExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expCall_);
  OnNodeEnter(nodeName);

  lastVisitedNodeType_ = NodeTypes::Other;

  OnNodeExit(nodeName);
}

void TraceFormationVisitor::Visit(const EseqExpression* expression) {
  std::string nodeName = GenerateNodeName(NodeNames::expEseq_);
  OnNodeEnter(nodeName);

  assert(false);  // such calls should never happen

  OnNodeExit(nodeName);
}

/*__________ Statements __________*/

void TraceFormationVisitor::Visit(const ExpStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statExp_);
  OnNodeEnter(nodeName);

  lastVisitedNodeType_ = NodeTypes::Other;

  OnNodeExit(nodeName);
}

void TraceFormationVisitor::Visit(const JumpConditionalStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statCJump_);
  OnNodeEnter(nodeName);

  lastVisitedNodeType_ = NodeTypes::Jump;

  OnNodeExit(nodeName);
}

void TraceFormationVisitor::Visit(const JumpStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statJump_);
  OnNodeEnter(nodeName);

  lastVisitedNodeType_ = NodeTypes::Jump;

  OnNodeExit(nodeName);
}

void TraceFormationVisitor::Visit(const LabelStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statLabel_);
  OnNodeEnter(nodeName);

  lastVisitedNodeType_ = NodeTypes::Label;
  lastVisitedLabel_ = std::make_shared<Address>(statement->Label());

  OnNodeExit(nodeName);
}

void TraceFormationVisitor::Visit(const MoveStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statMove_);
  OnNodeEnter(nodeName);

  lastVisitedNodeType_ = NodeTypes::Other;

  OnNodeExit(nodeName);
}

void TraceFormationVisitor::Visit(const SeqStatement* statement) {
  std::string nodeName = GenerateNodeName(NodeNames::statSeq_);
  OnNodeEnter(nodeName);

  assert(false);  // such calls should never happen

  OnNodeExit(nodeName);
}

/*__________  Lists __________*/

void TraceFormationVisitor::Visit(const ExpressionList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::listExp_);
  OnNodeEnter(nodeName);

  lastVisitedNodeType_ = NodeTypes::Other;

  OnNodeExit(nodeName);
}

void TraceFormationVisitor::Visit(const StatementList* list) {
  std::string nodeName = GenerateNodeName(NodeNames::listStat_);
  OnNodeEnter(nodeName);

  std::unique_ptr<Cg::Block> block;

  NodeTypes previousNodeType = NodeTypes::Jump;

  const std::vector<std::unique_ptr<const Statement>>& statements =
      list->Statements();
  for (auto it = statements.begin(); it != statements.end(); ++it) {
    (*it)->Accept(this);

    if (lastVisitedNodeType_ == NodeTypes::Label ||
        previousNodeType == NodeTypes::Jump) {
      if (block) {
        FinalizeBlockAndSave(std::move(block), previousNodeType, false);
      }
      block = std::move(StartNewBlock());
    }
    block->Add(std::move((*it)->Clone()));

    previousNodeType = lastVisitedNodeType_;
  }
  if (block) {
    FinalizeBlockAndSave(std::move(block), previousNodeType, true);
  }

  OnNodeExit(nodeName);
}

void TraceFormationVisitor::FinalizeBlockAndSave(
    std::unique_ptr<Cg::Block> block, NodeTypes previousNodeType,
    bool isLastBlock) {
  if (previousNodeType != NodeTypes::Jump) {
    Address jumpLabel =
        isLastBlock ? Address(EndBlockLabelName()) : *lastVisitedLabel_;
    block->Add(new JumpStatement(jumpLabel));
  }
  lastVisitedLabel_ = nullptr;
  trace_->push_back(
      std::move(std::unique_ptr<const Cg::Block>(block.release())));
}

std::unique_ptr<Cg::Block> TraceFormationVisitor::StartNewBlock() {
  std::unique_ptr<Cg::Block> block(new Cg::Block());
  if (lastVisitedNodeType_ != NodeTypes::Label) {
    block->Add(new LabelStatement(Address()));
  }
  return std::move(block);
}
