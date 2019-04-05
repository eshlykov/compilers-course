#pragma once

#include <memory>
#include "../frame/code-fragment.hpp"
#include "linerizer.hpp"

namespace Ct {

void Canonize(std::shared_ptr<CodeFragment> codeFragment) {
  Linearizer linerizer;
  while (codeFragment != nullptr) {
    linerizer.Visit(codeFragment->body_.get());
    codeFragment = codeFragment->next_;
  }
}

}  // namespace Ct
