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

  virtual void Visit(BinaryOperator* node) override final;

  virtual void Visit(Call* node) override final;

  virtual void Visit(ConditionalJump* node) override final;

  virtual void Visit(Constant* node) override final;

  virtual void Visit(ExpressionSequence* node) override final;

  virtual void Visit(Jump* node) override final;

  virtual void Visit(Label* node) override final;

  virtual void Visit(Memory* node) override final;

  virtual void Visit(Move* node) override final;

  virtual void Visit(Name* node) override final;

  virtual void Visit(StatementSequence* node) override final;

  virtual void Visit(Temporary* node) override final;

  virtual void Visit(Void* node) override final;

 private:
  std::shared_ptr<Ct::CodeFragment> codeFragment_;
  std::shared_ptr<Ct::Expression> exp_;
  std::shared_ptr<Ct::Statement> statement_;

 private:
  std::optional<Ct::ArithmeticOperator> ToCtArithmeticOperator(
      ArithmeticOperator arithmeticOperator);
  std::optional<Ct::LogicalOperator> ToCtLogicalOperator(
      LogicalOperator logicalOperator);
};

}  // namespace Irt
