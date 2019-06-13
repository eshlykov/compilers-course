#pragma once

#include <irt/node/node-names.hpp>
#include <irt/visitor/visitor.hpp>

#include <irt/node/expression-list.hpp>
#include <irt/node/expression.hpp>
#include <irt/node/statement.hpp>

#include <cg/node/patterns.hpp>

#include <memory>
#include <vector>

using namespace Irt;

namespace Cg {

class TilingVisitor : public Irt::Visitor {
 public:
  TilingVisitor(const IrtVt* root, bool verbose = false)
      : Visitor(verbose), root_(root) {
    InstantiatePatterns<
        TempPattern, LabelPattern, AddPattern, SubPattern, MultPattern,
        DivPattern, SubConstPattern, AddConstLeftPattern, AddConstRightPattern,
        ConstPattern, LoadMemoryPattern, LoadConstMemoryPattern,
        LoadMemoryLeftOffsetPattern, LoadMemoryRightOffsetPattern,
        StoreMemoryPattern, StoreConstMemoryPattern,
        StoreMemoryLeftOffsetPattern, StoreMemoryRightOffsetPattern,
        StoreRegisterPattern, CallFunctionPattern, JumpPattern,
        ConditionalJumpPattern, ExpStatementPattern>();
  }
  ~TilingVisitor() {}

  template <class First, class Second, class... Rest>
  void InstantiatePatterns() {
    InstantiatePatterns<First>();
    InstantiatePatterns<Second, Rest...>();
  }

  template <class Pattern>
  void InstantiatePatterns() {
    patterns_.push_back(std::unique_ptr<Pattern>(new Pattern(&dynamic_)));
  }

  void ApplyPatterns(const IrtVt* node) {
    for (const auto& pattern : patterns_) {
      pattern->Consume(node);
    }
  }

  // Visitors for different node types.
  void Visit(const ConstExpression* expression) override;
  void Visit(const NameExpression* expression) override;
  void Visit(const Irt::TempExpression* expression) override;
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

  const Command* Result() const { return dynamic_.at(root_).second.get(); }

 private:
  Dynamic dynamic_;
  std::vector<std::unique_ptr<Pattern>> patterns_;
  const IrtVt* root_;
};

}  // namespace Cg
