#pragma once

#include <memory>
#include <vector>
#include "node.hpp"

namespace Ct {

class Expression : public Node {
 public:
  virtual std::vector<std::shared_ptr<Expression>> Kids() = 0;

  virtual std::shared_ptr<Expression> Build(
      const std::vector<std::shared_ptr<Expression>>& expressionList) = 0;
};

}  // namespace Ct
