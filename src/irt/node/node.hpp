#pragma once

#include <cassert>
#include "../visitor/visitor.hpp"

namespace Irt {

class Node {
 public:
  Node() = default;

  virtual ~Node() = default;

  virtual void Accept(Visitor *) = 0;
};

}  // namespace Irt
