#pragma once

#include <cg/visitor/visitor.hpp>

namespace Cg {

class VisitorTarget {
 public:
  virtual ~VisitorTarget() = default;

  virtual void Accept(IVisitor* visitor) const = 0;
};

}  // namespace Cg
