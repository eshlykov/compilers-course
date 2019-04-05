#pragma once

#include <memory>
#include "../../utils/irt.hpp"

namespace Irt {

class Wrapper {
 public:
  virtual ~Wrapper() = default;

  virtual std::shared_ptr<Expression> ToRValue() const = 0;

  virtual std::shared_ptr<Statement> ToCondition(Address addressIf,
                                                 Address addressElse) const = 0;
};

}  // namespace Irt
