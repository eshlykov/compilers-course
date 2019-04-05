#pragma once

#include <memory>
#include "statement.hpp"

namespace Ct {

class StatementSequence : public Statement {
 public:
  StatementSequence(StatementPtr leftStatement, StatementPtr rightStatement);

  void Accept(Visitor* visitor) final;

  std::vector<ExpressionPtr> Kids() final;

  StatementPtr Build(const std::vector<ExpressionPtr>& expressionList) final;

 public:
  const StatementPtr leftStatement_;
  const StatementPtr rightStatement_;
};

inline StatementSequence::StatementSequence(StatementPtr leftStatement,
                                            StatementPtr rightStatement)
    : leftStatement_{std::move(leftStatement)},
      rightStatement_{std::move(rightStatement)} {
  assert(leftStatement_ != nullptr);
  assert(rightStatement_ != nullptr);
}

inline void StatementSequence::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

inline std::vector<ExpressionPtr> StatementSequence::Kids() { return {}; }

inline StatementPtr StatementSequence::Build(
    const std::vector<ExpressionPtr>& expressionList) {
  return std::make_shared<StatementSequence>(leftStatement_, rightStatement_);
}

using StatementSequencePtr = std::shared_ptr<StatementSequence>;

}  // namespace Ct
