#pragma once

#include <memory>
#include "statement.hpp"

namespace Ct {

class Expression;

class Move : public Statement {
 public:
  Move(std::shared_ptr<Expression> destination,
       std::shared_ptr<Expression> source);

  virtual void Accept(Visitor* visitor) override final;

  virtual std::vector<std::shared_ptr<Expression>> Kids() override final;

  virtual std::shared_ptr<Statement> Build(
      const std::vector<std::shared_ptr<Expression>>& expressionList)
      override final;

 public:
  const std::shared_ptr<Expression> destination_;
  const std::shared_ptr<Expression> source_;
};

inline Move::Move(std::shared_ptr<Expression> destination,
                  std::shared_ptr<Expression> source)
    : destination_{destination}, source_{source} {
  assert(destination_ != nullptr);
  assert(source_ != nullptr);
}

inline void Move::Accept(Visitor* visitor) { visitor->Visit(this); }

inline std::vector<std::shared_ptr<Expression>> Move::Kids() {
  if (std::dynamic_pointer_cast<Memory>(destination_) != nullptr) {
    return {std::dynamic_pointer_cast<Memory>(destination_), source_};
  } else {
    return {source_};
  }
}

inline std::shared_ptr<Statement> Move::Build(
    const std::vector<std::shared_ptr<Expression>>& expressionList) {
  if (std::dynamic_pointer_cast<Memory>(destination_) != nullptr) {
    return std::make_shared<Move>(std::make_shared<Memory>(expressionList[0]),
                                  expressionList[1]);
  } else {
    return std::make_shared<Move>(destination_, expressionList[0]);
  }
}

}  // namespace Ct
