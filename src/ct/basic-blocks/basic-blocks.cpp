#include <utility>

#include <utility>

#include <memory>
#include "basic-blocks.hpp"

namespace Ct {

void BasicBlocks::CreateBasicBlocks(
    const std::vector<StatementPtr>& statements) {
  MakeBlocks(statements);
}

Address BasicBlocks::GetDone() { return done_; }

std::shared_ptr<StatementListList> BasicBlocks::GetBlocks() { return blocks_; }

void BasicBlocks::SetBlocks(std::shared_ptr<StatementListList> blocks) {
  blocks_ = std::move(blocks);
}

void BasicBlocks::AddStatement(StatementPtr statement) {
  lastStatement_.push_back(statement);
}

void BasicBlocks::DoStatements(const std::vector<StatementPtr>& statements) {
  if (statements.empty()) {
    std::vector<StatementPtr> jumpStatements = {std::make_shared<Jump>(done_)};
    DoStatements(jumpStatements);
    return;
  }

  auto jump = std::dynamic_pointer_cast<Jump>(statements[0]);
  auto label = std::dynamic_pointer_cast<Label>(statements[0]);
  auto conditionalJump =
      std::dynamic_pointer_cast<ConditionalJump>(statements[0]);

  if (jump != nullptr || conditionalJump != nullptr) {
    auto statementsTail =
        std::vector<StatementPtr>(statements.begin() + 1, statements.end());
    AddStatement(statements[0]);
    MakeBlocks(statementsTail);
  } else if (label != nullptr) {
    auto copy = statements;
    copy.insert(copy.begin(), std::make_shared<Jump>(label->address_));
    DoStatements(copy);
  } else {
    auto statementsTail =
        std::vector<StatementPtr>(statements.begin() + 1, statements.end());
    AddStatement(statements[0]);
    DoStatements(statementsTail);
  }
}

void BasicBlocks::MakeBlocks(const std::vector<StatementPtr>& statements) {
  if (statements.empty()) {
    return;
  }

  if (auto label = std::dynamic_pointer_cast<Label>(statements[0]);
      label != nullptr) {
    lastStatement_ = {statements[0]};
    if (lastBlock_ == nullptr) {
      auto block = blocks_;
      if (block == nullptr) {
        blocks_ = std::make_shared<StatementListList>(lastStatement_, nullptr);
      } else {
        while (block->tail_ != nullptr) {
          block = block->tail_;
        }
        block->tail_ = std::make_shared<StatementListList>(lastStatement_, nullptr);
      }
      auto last = lastBlock_;
      if (last == nullptr) {
        lastBlock_ = std::make_shared<StatementListList>(lastStatement_, nullptr);;
      } else {
        while (last->tail_ != nullptr) {
          last = last->tail_;
        }
        last->tail_ = std::make_shared<StatementListList>(lastStatement_, nullptr);
      }
    } else {
      auto last = lastBlock_;
      if (last == nullptr) {
        lastBlock_ = std::make_shared<StatementListList>(lastStatement_, nullptr);;
      } else {
        while (last->tail_ != nullptr) {
          last = last->tail_;
        }
        last->tail_ = std::make_shared<StatementListList>(lastStatement_, nullptr);
      }
    }
    auto statementsTail =
        std::vector<StatementPtr>(statements.begin() + 1, statements.end());
    DoStatements(statementsTail);
  } else {
    auto copy = statements;
    copy.insert(copy.begin(), std::make_shared<Label>(Address()));
    MakeBlocks(copy);
  }
}

}  // namespace Ct
