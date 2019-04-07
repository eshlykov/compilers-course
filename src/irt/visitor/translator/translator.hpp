#pragma once

#include <memory>
#include <optional>
#include "../../../ct/frame/code-fragment.hpp"
#include "../../../ct/node/node.hpp"
#include "../../../utils/ct.hpp"
#include "../../../utils/irt.hpp"
#include "../visitor.hpp"

namespace Irt {

class Translator : public Visitor {
 public:
  Translator();

  void Visit(BinaryOperator* node) final;

  void Visit(Call* node) final;

  void Visit(ConditionalJump* node) final;

  void Visit(Constant* node) final;

  void Visit(ExpressionSequence* node) final;

  void Visit(Jump* node) final;

  void Visit(Label* node) final;

  void Visit(Memory* node) final;

  void Visit(Move* node) final;

  void Visit(Name* node) final;

  void Visit(StatementSequence* node) final;

  void Visit(Temporary* node) final;

  void Visit(Void* node) final;

  std::shared_ptr<Ct::Statement> GetStatement();

 private:
  std::shared_ptr<Ct::CodeFragment> codeFragment_;
  std::shared_ptr<Ct::Expression> expression_;
  std::shared_ptr<Ct::Statement> statement_;

 private:
  static Ct::ArithmeticOperator ToCtArithmeticOperator(
      ArithmeticOperator arithmeticOperator);
  static Ct::LogicalOperator ToCtLogicalOperator(
      LogicalOperator logicalOperator);
};

}  // namespace Irt
