#pragma once

#include <memory>
#include <string>
#include "../../frame/code-fragment.hpp"
#include "printer.hpp"

namespace Ct {

void Print(const std::string& filename,
           std::shared_ptr<CodeFragment> codeFragment) {
  Printer printer{filename};
  while (codeFragment != nullptr) {
    StatementSequencePtr body = codeFragment->body_;
    std::vector<Statement> statements = Linearizer::Linearize(body);
    for (auto&& statement : statements) {
      printer.Visit(statement);
      printer.Next();
    }
    codeFragment = codeFragment->next_;
  }
}

}  // namespace Ct
