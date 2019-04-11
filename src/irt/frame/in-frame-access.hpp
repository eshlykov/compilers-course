#pragma once

#include "../node/binary-operator.hpp"
#include "../node/constant.hpp"
#include "../node/memory.hpp"
#include "../node/temporary.hpp"
#include "access.hpp"

namespace Irt {

class InFrameAccess : public Access {
 public:
  explicit InFrameAccess(const Storage& framePointer, int offset);

  std::shared_ptr<Expression> GetData() const final;

 private:
  const Storage& framePointer_;
  int offset_;
};

}  // namespace Irt
