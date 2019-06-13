#pragma once

#include <irt/visitor/visitor.hpp>

namespace Irt {

class IVisitorTarget {
 public:
  virtual ~IVisitorTarget() {}
  virtual void Accept(IVisitor* visitor) const = 0;
};

}  // namespace Irt
