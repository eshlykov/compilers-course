#pragma once

#include <memory>
#include "statement.hpp"

namespace Irt {

class StatementSequence : public Statement {
 public:
  StatementSequence(std::shared_ptr<Statement> leftStatement,
                    std::shared_ptr<Statement> rightStatement);

  void Accept(Visitor *visitor) final;

 public:
  const std::shared_ptr<Statement> leftStatement_;
  const std::shared_ptr<Statement> rightStatement_;
};

inline StatementSequence::StatementSequence(
    std::shared_ptr<Statement> leftStatement,
    std::shared_ptr<Statement> rightStatement)
    : leftStatement_{std::move(leftStatement)},
      rightStatement_{std::move(rightStatement)} {
  assert(leftStatement_ != nullptr);
  assert(rightStatement_ != nullptr);
}

inline void StatementSequence::Accept(Visitor *visitor) {
  visitor->Visit(this);
}

}  // namespace Irt
