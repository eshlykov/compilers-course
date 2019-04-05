#pragma once

#include <memory>
#include <vector>
#include "../../utils/ct.hpp"

namespace Ct {

struct StatementExpressionList {
  StatementExpressionList(StatementPtr statement,
                          std::vector<ExpressionPtr> expressions);

  StatementPtr Statement_;
  std::vector<ExpressionPtr> Expressions_;
};

inline StatementExpressionList::StatementExpressionList(
    StatementPtr statement, std::vector<ExpressionPtr> expressions)
    : Statement_(std::move(statement)), Expressions_(std::move(expressions)) {}

}  // namespace Ct
