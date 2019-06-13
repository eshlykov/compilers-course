#pragma once

#include <memory>

#include <irt/node/node-names.hpp>
#include <irt/visitor/visitor.hpp>

#include <irt/node/expression-list.hpp>
#include <irt/node/expression.hpp>
#include <irt/node/statement.hpp>
#include <utils/address.hpp>

#include <cg/trace/trace.hpp>

namespace Irt {

class TraceFormationVisitor : public Visitor {
 public:
  TraceFormationVisitor(bool verbose = false)
      : Visitor(verbose),
        lastVisitedNodeType_(NodeTypes::Other),
        trace_(new Cg::Trace()) {}
  ~TraceFormationVisitor() {}

  std::unique_ptr<Cg::Trace> Trace();
  static std::string EndBlockLabelName();

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
  enum class NodeTypes : char { Label, Jump, Other };

  void FinalizeBlockAndSave(std::unique_ptr<Cg::Block> block,
                            NodeTypes previousNodeType, bool isLastBlock);
  std::unique_ptr<Cg::Block> StartNewBlock();

  std::shared_ptr<Address> lastVisitedLabel_;
  NodeTypes lastVisitedNodeType_;
  std::unique_ptr<Cg::Trace> trace_;
};

}  // namespace Irt
