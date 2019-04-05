#pragma once

#include <memory>
#include "statement.hpp"

namespace Ct {

class Expression;

class Move : public Statement {
 public:
  Move(ExpressionPtr destination, ExpressionPtr source);

  void Accept(Visitor* visitor) final;

  std::vector<ExpressionPtr> Kids() final;

  StatementPtr Build(const std::vector<ExpressionPtr>& expressionList) final;

 public:
  const ExpressionPtr destination_;
  const ExpressionPtr source_;
};

inline Move::Move(ExpressionPtr destination, ExpressionPtr source)
    : destination_{std::move(destination)}, source_{std::move(source)} {
  assert(destination_ != nullptr);
  assert(source_ != nullptr);
}

inline void Move::Accept(Visitor* visitor) { visitor->Visit(this); }

inline std::vector<ExpressionPtr> Move::Kids() {
  auto memory = std::dynamic_pointer_cast<Memory>(destination_);
  if (memory != nullptr) {
    return {memory, source_};
  }
  return {source_};
}

inline StatementPtr Move::Build(
    const std::vector<ExpressionPtr>& expressionList) {
  auto memory = std::dynamic_pointer_cast<Memory>(destination_);
  if (memory != nullptr) {
    return std::make_shared<Move>(std::make_shared<Memory>(expressionList[0]),
                                  expressionList[1]);
  }
  return std::make_shared<Move>(destination_, expressionList[0]);
}

using MovePtr = std::shared_ptr<Move>;

}  // namespace Ct
