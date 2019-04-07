#include "frame.hpp"
#include <algorithm>
#include <cassert>

namespace Ct {

const Storage Frame::FramePointer_;

Frame::Frame(const std::shared_ptr<Irt::Frame>& frame)
    : name_(frame->name_), size_(frame->Size()) {
  for (const auto& parameter : frame->GetFormalParameters()) {
    formalParameters_.push_back(parameter.first);
  }

  for (const auto& variable : frame->GetLocalVariables()) {
    localVariables_.push_back(variable.first);
  }
}

}  // namespace Ct
