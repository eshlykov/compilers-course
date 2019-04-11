#pragma once

#include "../node/binary-operator.hpp"
#include "../node/constant.hpp"
#include "../node/memory.hpp"
#include "../node/temporary.hpp"
#include "access.hpp"

namespace Ct {

class InFrameAccess : public Access {
 public:
  explicit InFrameAccess(const Storage& framePointer, int offset);

  ExpressionPtr GetData() const final;

 private:
  const Storage& framePointer_;
  int offset_;
};

}  // namespace Ct
