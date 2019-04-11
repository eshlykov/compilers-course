#include "in-frame-access.hpp"
#include "frame.hpp"

namespace Ct {

InFrameAccess::InFrameAccess(const Storage& framePointer, int offset)
    : framePointer_{framePointer}, offset_{offset} {}

ExpressionPtr InFrameAccess::GetData() const {
  if (offset_ == 0) {
    return std::make_shared<Memory>(std::make_shared<Temporary>(framePointer_));
  } else {
    return std::make_shared<Memory>(std::make_shared<BinaryOperator>(
        ArithmeticOperator::Plus, std::make_shared<Temporary>(framePointer_),
        std::make_shared<Constant>(offset_)));
  }
}

}  // namespace Ct
