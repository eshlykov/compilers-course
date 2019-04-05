#pragma once

#include <memory>
#include "statement.hpp"

namespace Ct {

class StatementSequence : public Statement {
 public:
  StatementSequence(std::shared_ptr<Statement> leftStatement,
                    std::shared_ptr<Statement> rightStatement);

  virtual void Accept(Visitor* visitor) override final;

  virtual std::vector<std::shared_ptr<Expression>> Kids() override final;

  virtual std::shared_ptr<Statement> Build(
      const std::vector<std::shared_ptr<Expression>>& expressionList)
      override final;

 public:
  const std::shared_ptr<Statement> leftStatement_;
  const std::shared_ptr<Statement> rightStatement_;
};

inline StatementSequence::StatementSequence(
    std::shared_ptr<Statement> leftStatement,
    std::shared_ptr<Statement> rightStatement)
    : leftStatement_{leftStatement}, rightStatement_{rightStatement} {
  assert(leftStatement_ != nullptr);
  assert(rightStatement_ != nullptr);
}

inline void StatementSequence::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

inline std::vector<std::shared_ptr<Expression>> StatementSequence::Kids() {
  return {};
}

inline std::shared_ptr<Statement> StatementSequence::Build(
    const std::vector<std::shared_ptr<Expression>>& expressionList) {
  return std::make_shared<StatementSequence>(leftStatement_, rightStatement_);
}

}  // namespace Ct
