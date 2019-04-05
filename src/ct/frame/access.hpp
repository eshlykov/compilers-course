#pragma once

#include <memory>
#include "../node/expression.hpp"

namespace Ct {

class Access {
 public:
  virtual ~Access() = default;

  virtual std::shared_ptr<Expression> GetData() const = 0;
};

}  // namespace Ct
