#pragma once

#include <memory>
#include "../node/expression.hpp"

namespace Irt {

class Access {
 public:
  virtual ~Access() = default;

  virtual std::shared_ptr<Expression> GetData() const = 0;
};

}  // namespace Irt
