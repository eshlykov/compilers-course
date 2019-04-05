#pragma once

#include "../node/binary-operator.hpp"
#include "../node/constant.hpp"
#include "../node/memory.hpp"
#include "../node/temporary.hpp"
#include "access.hpp"

namespace Ct {

class InFrameAccess : public Access {
 public:
  explicit InFrameAccess(int offset);

  std::shared_ptr<Expression> GetData() const final;

 private:
  int offset_;
};

}  // namespace Ct
