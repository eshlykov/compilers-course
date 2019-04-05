#pragma once

#include <memory>
#include "statement.hpp"

namespace Irt {

class StatementSequence : public Statement {
 public:
  StatementSequence(std::shared_ptr<Statement> leftStatement,
                    std::shared_ptr<Statement> rightStatement);

  virtual void Accept(Visitor* visitor) override final;

 public:
  const std::shared_ptr<Statement> leftStatement_;
  const std::shared_ptr<Statement> rightStatement_;
};

}  // namespace Irt
