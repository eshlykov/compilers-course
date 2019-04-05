#pragma once

#include <memory>
#include "statement.hpp"

namespace Ct {

class Expression;

class Move : public Statement {
 public:
  Move(std::shared_ptr<Expression> destination,
       std::shared_ptr<Expression> source);

  void Accept(Visitor *visitor) final;

  std::vector<std::shared_ptr<Expression>> Kids() final;

  std::shared_ptr<Statement> Build(
      const std::vector<std::shared_ptr<Expression>> &expressionList) final;

 public:
  const std::shared_ptr<Expression> destination_;
  const std::shared_ptr<Expression> source_;
};

inline Move::Move(std::shared_ptr<Expression> destination,
                  std::shared_ptr<Expression> source)
    : destination_{std::move(destination)}, source_{std::move(source)} {
  assert(destination_ != nullptr);
  assert(source_ != nullptr);
}

inline void Move::Accept(Visitor *visitor) { visitor->Visit(this); }

inline std::vector<std::shared_ptr<Expression>> Move::Kids() {
  auto memory = std::dynamic_pointer_cast<Memory>(destination_);
  if (memory != nullptr) {
    return {memory, source_};
  }
  return {source_};
}

inline std::shared_ptr<Statement> Move::Build(
    const std::vector<std::shared_ptr<Expression>> &expressionList) {
  auto memory = std::dynamic_pointer_cast<Memory>(destination_);
  if (memory != nullptr) {
    return std::make_shared<Move>(std::make_shared<Memory>(expressionList[0]),
                                  expressionList[1]);
  }
  return std::make_shared<Move>(destination_, expressionList[0]);
}

}  // namespace Ct
