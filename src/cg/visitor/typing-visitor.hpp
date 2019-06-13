#pragma once

#include <irt/node/expression.hpp>
#include <irt/visitor/visitor.hpp>

using namespace Irt;

namespace Cg {

template <typename T>
class TypingVisitor : public Irt::Visitor {
 public:
  explicit TypingVisitor(bool verbose = false)
      : Visitor(verbose), node_(nullptr) {}
  ~TypingVisitor() override = default;

  // Visitors for different node types.
  void Visit(const Irt::ConstExpression* expression) override{};
  void Visit(const Irt::NameExpression* expression) override{};
  void Visit(const Irt::TempExpression* expression) override{};
  void Visit(const Irt::BinaryExpression* expression) override{};
  void Visit(const Irt::MemExpression* expression) override{};
  void Visit(const Irt::CallExpression* expression) override{};
  void Visit(const Irt::EseqExpression* expression) override{};

  void Visit(const Irt::ExpStatement* statement) override{};
  void Visit(const Irt::JumpConditionalStatement* statement) override{};
  void Visit(const Irt::JumpStatement* statement) override{};
  void Visit(const Irt::LabelStatement* statement) override{};
  void Visit(const Irt::MoveStatement* statement) override{};
  void Visit(const Irt::SeqStatement* statement) override{};

  void Visit(const Irt::ExpressionList* list) override{};
  void Visit(const Irt::StatementList* list) override{};

  const T* GetNode();

 private:
  const T* node_;
};

template <>
void TypingVisitor<Irt::ConstExpression>::Visit(
    const Irt::ConstExpression* expression) {
  node_ = expression;
}

template <>
void TypingVisitor<Irt::NameExpression>::Visit(
    const Irt::NameExpression* expression) {
  node_ = expression;
}

template <>
void TypingVisitor<Irt::TempExpression>::Visit(
    const Irt::TempExpression* expression) {
  node_ = expression;
}

template <>
void TypingVisitor<Irt::BinaryExpression>::Visit(
    const Irt::BinaryExpression* expression) {
  node_ = expression;
}

template <>
void TypingVisitor<Irt::MemExpression>::Visit(
    const Irt::MemExpression* expression) {
  node_ = expression;
}

template <>
void TypingVisitor<Irt::CallExpression>::Visit(
    const Irt::CallExpression* expression) {
  node_ = expression;
}

template <>
void TypingVisitor<Irt::EseqExpression>::Visit(
    const Irt::EseqExpression* expression) {
  node_ = expression;
}

template <>
void TypingVisitor<Irt::ExpStatement>::Visit(
    const Irt::ExpStatement* statement) {
  node_ = statement;
}

template <>
void TypingVisitor<Irt::JumpConditionalStatement>::Visit(
    const Irt::JumpConditionalStatement* statement) {
  node_ = statement;
}

template <>
void TypingVisitor<Irt::JumpStatement>::Visit(
    const Irt::JumpStatement* statement) {
  node_ = statement;
}

template <>
void TypingVisitor<Irt::LabelStatement>::Visit(
    const Irt::LabelStatement* statement) {
  node_ = statement;
}

template <>
void TypingVisitor<Irt::MoveStatement>::Visit(
    const Irt::MoveStatement* statement) {
  node_ = statement;
}

template <>
void TypingVisitor<Irt::SeqStatement>::Visit(
    const Irt::SeqStatement* statement) {
  node_ = statement;
}

template <>
void TypingVisitor<Irt::ExpressionList>::Visit(
    const Irt::ExpressionList* list) {
  node_ = list;
}

template <>
void TypingVisitor<Irt::StatementList>::Visit(const Irt::StatementList* list) {
  node_ = list;
}

template <typename T>
const T* TypingVisitor<T>::GetNode() {
  return node_;
}

}  // namespace Cg
