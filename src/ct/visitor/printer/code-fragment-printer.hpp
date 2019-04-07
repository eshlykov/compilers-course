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
      printer.Visit(statement.get());
      printer.Next();
    }
    codeFragment = codeFragment->next_;
  }
}

}  // namespace Ct
