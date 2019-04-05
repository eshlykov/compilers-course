#pragma once

#include <cassert>
#include "../../utils/location.hpp"
#include "../visitor/visitor.hpp"

namespace Ast {

enum class TypeKind {
  Undefined,
  IntArray,
  Boolean,
  Int,
};

class Node {
 public:
  Node() = default;

  virtual ~Node() = default;

  virtual void Accept(Visitor *) = 0;

  void SetLocation(const Location &location);

  const Location &GetLocation() const;

 private:
  Location location_;
};

inline void Node::SetLocation(const Location &location) {
  location_ = location;
}

inline const Location &Node::GetLocation() const { return location_; }

}  // namespace Ast
