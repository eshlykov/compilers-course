#pragma once

#include <memory>
#include <vector>
#include "expression.hpp"
#include "node.hpp"

namespace Ct {

class Statement : public Node {
 public:
  virtual std::vector<ExpressionPtr> Kids() = 0;

  virtual std::shared_ptr<Statement> Build(
      const std::vector<ExpressionPtr>& expressionList) = 0;
};

using StatementPtr = std::shared_ptr<Statement>;

}  // namespace Ct
