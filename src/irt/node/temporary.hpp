#pragma once

#include <memory>
#include <string>
#include "../../utils/storage.hpp"
#include "expression.hpp"

namespace Irt {

class Temporary : public Expression {
 public:
  explicit Temporary(Storage storage);

  virtual void Accept(Visitor* visitor) override final;

 public:
  const Storage storage_;
};

}  // namespace Irt
