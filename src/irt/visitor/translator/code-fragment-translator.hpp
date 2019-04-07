#pragma once

#include <memory>
#include <string>
#include "../../../ct/frame/code-fragment.hpp"
#include "../../frame/code-fragment.hpp"
#include "printer.hpp"

namespace Irt {

std::shared_ptr<Ct::CodeFragment> Translate(std::shared_ptr<CodeFragment> codeFragment) {
  Translator translator;
  std::shared_ptr<Ct::CodeFragment> head = nullptr;
  std::shared_ptr<Ct::CodeFragment> tail = nullptr;

  while (codeFragment != nullptr) {
    translator.Visit(codeFragment->body_.get());
    auto temp = std::make_shared<Ct::CodeFragment>(translator.GetStatement(), codeFragment->frame_);

    if (head == nullptr) {
      head = temp;
      tail = temp;
    } else {
      tail->next = temp;
      tail = temp;
    }

    codeFragment = codeFragment->next_;
  }

  return head;
}

}  // namespace Irt
