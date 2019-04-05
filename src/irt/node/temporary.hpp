#pragma once

#include <memory>
#include <string>
#include "../../utils/storage.hpp"
#include "expression.hpp"

namespace Irt {

class Temporary : public Expression {
 public:
  explicit Temporary(Storage storage);

  void Accept(Visitor *visitor) final;

 public:
  const Storage storage_;
};

inline Temporary::Temporary(Storage storage) : storage_(storage) {}

inline void Temporary::Accept(Visitor *visitor) { visitor->Visit(this); }

}  // namespace Irt
