#pragma once

#include <vector>
#include "statement-list-list.hpp"

namespace Ct {

class BasicBlocks {
 public:
  BasicBlocks() = default;

  void CreateBasicBlocks(const std::vector<StatementPtr>& statements);

 private:
  void AddStatement(StatementPtr statement);

  void DoStatements(const std::vector<StatementPtr>& statements);

  void MakeBlocks(const std::vector<StatementPtr>& statements);

 public:
  Address done_;
  std::vector<StatementPtr> lastStatement_;
  std::shared_ptr<StatementListList> blocks_;
  std::shared_ptr<StatementListList> lastBlock_;
};

}  // namespace Ct
