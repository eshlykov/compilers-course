#pragma once

#include <cassert>
#include "../visitor/visitor.hpp"

namespace Ct {

class Node {
 public:
  Node() = default;

  virtual ~Node() = default;

  virtual void Accept(Visitor*) = 0;
};

using NodePtr = std::shared_ptr<Node>;

}  // namespace Ct
