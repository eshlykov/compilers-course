#pragma once

#include <memory>
#include <vector>
#include "../../utils/ct.hpp"

namespace Ct {

struct StatementListList {
  StatementListList(std::vector<StatementPtr> head,
                    std::shared_ptr<StatementListList> tail);

  std::vector<StatementPtr> head_;
  std::shared_ptr<StatementListList> tail_;
};

inline StatementListList::StatementListList(
    std::vector<StatementPtr> head, std::shared_ptr<StatementListList> tail)
    : head_(std::move(head)), tail_(std::move(tail)) {}

}  // namespace Ct
