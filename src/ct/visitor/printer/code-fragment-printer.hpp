#pragma once

#include <memory>
#include <string>
#include "../../frame/code-fragment.hpp"
#include "../../linearizer/linerizer.hpp"
#include "printer.hpp"

namespace Ct {

void Print(const std::string& filename,
           std::shared_ptr<CodeFragment> codeFragment) {
  Printer printer{filename};
  Linearizer linearizer;

  while (codeFragment != nullptr) {
    StatementSequencePtr body = codeFragment->body_;
    std::vector<StatementPtr> statements = linearizer.Linearize(body);
    for (auto&& statement : statements) {
      if (auto tmp = std::dynamic_pointer_cast<ConditionalJump>(statement);
          tmp != nullptr) {
        printer.Visit(tmp.get());
      } else if (auto jump = std::dynamic_pointer_cast<Jump>(statement);
                 jump != nullptr) {
        printer.Visit(jump.get());
      } else if (auto label = std::dynamic_pointer_cast<Label>(statement);
                 label != nullptr) {
        printer.Visit(label.get());
      } else if (auto move = std::dynamic_pointer_cast<Move>(statement);
                 move != nullptr) {
        printer.Visit(move.get());
      } else if (auto statementSequence =
                     std::dynamic_pointer_cast<StatementSequence>(statement);
                 statementSequence != nullptr) {
        printer.Visit(statementSequence.get());
      } else if (auto voidStatement =
                     std::dynamic_pointer_cast<Void>(statement);
                 voidStatement != nullptr) {
        printer.Visit(voidStatement.get());
      }
      printer.Next();
    }
    codeFragment = codeFragment->next_;
  }
}

}  // namespace Ct
