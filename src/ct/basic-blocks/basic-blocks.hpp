#pragma once

#include <vector>
#include "statement-list-list.hpp"

namespace Ct {

class BasicBlocks {
 public:
  BasicBlocks() = default;

  void CreateBasicBlocks(const std::vector<StatementPtr>& statements);

  Address GetDone();

  std::shared_ptr<StatementListList> GetBlocks();

  void SetBlocks(std::shared_ptr<StatementListList>);

 private:
  void AddStatement(StatementPtr statement);

  void DoStatements(const std::vector<StatementPtr>& statements);

  void MakeBlocks(const std::vector<StatementPtr>& statements);

 private:
  Address done_;
  std::vector<StatementPtr> lastStatement_;
  std::shared_ptr<StatementListList> blocks_;
  std::shared_ptr<StatementListList> lastBlock_;
};

}  // namespace Ct
