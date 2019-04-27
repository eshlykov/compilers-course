#pragma once

#include "../node/statement.hpp"

#include <algorithm>
#include <memory>
#include <vector>

struct StatementList {
  explicit StatementList(const std::vector<StatementPtr>& statements) {
    if (!statements.empty()) {
      head_ = statements.front();

      std::vector<StatementList> tail;
      std::copy(statements.begin() + 1, statements.end(), std::back_inserter(tail));

      if (!tail.empty()) {
        tail_ = std::make_shared<StatementList>(tail);
      }
    }
  }

  std::vector<StatementPtr> ToStatements() {
    if (head_ == nullptr) {
      return {};
    }

    if (tail_ == nullptr) {
      return {head_};
    }

    std::vector<StatementPtr> head{head_};
    tail = tail_->ToStatements();
    head.insert(head.end(), tail.begin(). tail.end());

    return head;
  }

  StatementPtr head_{nullptr};
  std::shared_ptr<StatementList> tail_{nullptr};
};
