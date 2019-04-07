#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "../../utils/address.hpp"
#include "../../utils/storage.hpp"
#include "../node/expression.hpp"
#include "../../irt/frame/frame.hpp"
#include "in-frame-access.hpp"

namespace Ct {

class Frame {
 public:
  explicit Frame(const std::shared_ptr<Irt::Frame>& frame);

 private:

 public:
  static constexpr int WordSize_ = sizeof(nullptr);
  static const Storage FramePointer_;

 public:
  const Address returnAddress_;

 private:
  const std::string name_;
  int size_;
  std::vector<std::string> formalParameters_;
  std::vector<std::string> localVariables_;
};

}  // namespace Ct
