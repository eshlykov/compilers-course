#pragma once

#include <memory>
#include "expression.hpp"
#include "statement.hpp"

namespace Ast {

class ConditionStatement : public Statement {
 public:
  ConditionStatement(Location location, std::unique_ptr<Expression> condition,
                     std::unique_ptr<Statement> ifStatement,
                     std::unique_ptr<Statement> elseStatement);

  void Accept(Visitor* visitor) final;

 public:
  const std::unique_ptr<Expression> condition_;
  const std::unique_ptr<Statement> ifStatement_;
  const std::unique_ptr<Statement> elseStatement_;
};

inline ConditionStatement::ConditionStatement(
    Location location, std::unique_ptr<Expression> condition,
    std::unique_ptr<Statement> ifStatement,
    std::unique_ptr<Statement> elseStatement)
    : condition_{std::move(condition)},
      ifStatement_{std::move(ifStatement)},
      elseStatement_{std::move(elseStatement)} {
  SetLocation(location);
  assert(condition_ != nullptr);
  assert(ifStatement_ != nullptr);
  assert(elseStatement_ != nullptr);
}

inline void ConditionStatement::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

}  // namespace Ast
