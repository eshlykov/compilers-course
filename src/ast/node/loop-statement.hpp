#pragma once

#include <memory>
#include "expression.hpp"
#include "statement.hpp"

namespace Ast {

class LoopStatement : public Statement {
 public:
  LoopStatement(Location location, std::unique_ptr<Expression> condition,
                std::unique_ptr<Statement> statement);

  void Accept(Visitor* visitor) final;

 public:
  const std::unique_ptr<Expression> condition_;
  const std::unique_ptr<Statement> statement_;
};

inline LoopStatement::LoopStatement(Location location,
                                    std::unique_ptr<Expression> condition,
                                    std::unique_ptr<Statement> statement)
    : condition_(std::move(condition)), statement_(std::move(statement)) {
  SetLocation(location);
  assert(condition_ != nullptr);
  assert(statement_ != nullptr);
}

inline void LoopStatement::Accept(Visitor* visitor) { visitor->Visit(this); }

}  // namespace Ast
