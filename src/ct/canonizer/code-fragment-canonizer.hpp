#pragma once

#include <memory>
#include "../frame/code-fragment.hpp"
#include "canonizer.hpp"

namespace Ct {

void Canonize(std::shared_ptr<CodeFragment> codeFragment) {
  Canonizer canonizer;
  while (codeFragment != nullptr) {
    canonizer.Visit(codeFragment->body_.get());
    codeFragment = codeFragment->next_;
  }
}

}  // namespace Ct
