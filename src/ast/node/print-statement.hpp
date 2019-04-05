#pragma once

#include <memory>
#include "expression.hpp"
#include "statement.hpp"

namespace Ast {

class PrintStatement : public Statement {
 public:
  explicit PrintStatement(Location location,
                          std::unique_ptr<Expression> expression);

  void Accept(Visitor* visitor) final;

 public:
  const std::unique_ptr<Expression> expression_;
};

inline PrintStatement::PrintStatement(Location location,
                                      std::unique_ptr<Expression> expression)
    : expression_{std::move(expression)} {
  SetLocation(location);
  assert(expression_ != nullptr);
}

inline void PrintStatement::Accept(Visitor* visitor) { visitor->Visit(this); }

}  // namespace Ast
