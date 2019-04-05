#pragma once

#include <memory>
#include <vector>
#include "../../utils/ct.hpp"

namespace Ct {

struct StatementExpressionList {
  StatementExpressionList(std::shared_ptr<Statement> statement,
                          std::vector<std::shared_ptr<Expression>> expressions);

  std::shared_ptr<Statement> Statement_;
  std::vector<std::shared_ptr<Expression>> Expressions_;
};

inline StatementExpressionList::StatementExpressionList(
    std::shared_ptr<Statement> statement,
    std::vector<std::shared_ptr<Expression>> expressions)
    : Statement_(std::move(statement)), Expressions_(std::move(expressions)) {}

}  // namespace Ct
