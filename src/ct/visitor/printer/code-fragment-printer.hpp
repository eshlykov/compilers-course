#pragma once

#include <memory>
#include <string>
#include "../../frame/code-fragment.hpp"
#include "printer.hpp"
#include "../../linearizer/linerizer.hpp"

namespace Ct {

void Print(const std::string& filename,
           std::shared_ptr<CodeFragment> codeFragment) {
  Printer printer{filename};
  Linearizer linearizer;

  while (codeFragment != nullptr) {
    StatementSequencePtr body = codeFragment->body_;
    std::vector<StatementPtr> statements = linearizer.Linearize(body);
    for (auto&& statement : statements) {
      if (auto tmp = std::dynamic_pointer_cast<ConditionalJump>(statement); tmp != nullptr){
        printer.Visit(tmp.get());
      } else if (auto tmp = std::dynamic_pointer_cast<Jump>(statement); tmp != nullptr) {
        printer.Visit(tmp.get());
      } else if (auto tmp = std::dynamic_pointer_cast<Label>(statement); tmp != nullptr) {
        printer.Visit(tmp.get());
      } else if (auto tmp = std::dynamic_pointer_cast<Move>(statement); tmp != nullptr) {
        printer.Visit(tmp.get());
      } else if (auto tmp = std::dynamic_pointer_cast<StatementSequence>(statement); tmp != nullptr) {
        printer.Visit(tmp.get());
      } else if (auto tmp = std::dynamic_pointer_cast<Void>(statement); tmp != nullptr) {
        printer.Visit(tmp.get());
      }
      printer.Next();
    }
    codeFragment = codeFragment->next_;
  }
}

}  // namespace Ct
