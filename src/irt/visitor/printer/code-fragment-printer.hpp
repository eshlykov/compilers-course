#pragma once

#include <memory>
#include <string>
#include "../../frame/code-fragment.hpp"
#include "printer.hpp"

namespace Irt {

void Print(const std::string &filename,
           std::shared_ptr<CodeFragment> codeFragment) {
  Printer printer{filename};
  while (codeFragment != nullptr) {
    printer.Visit(codeFragment->body_.get());
    printer.Next();
    codeFragment = codeFragment->next_;
  }
}

}  // namespace Irt
