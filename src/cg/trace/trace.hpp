#pragma once

#include <vector>

#include <irt/node/statement.hpp>

namespace Cg {

using Block = Irt::StatementList;
using Trace = std::vector<std::unique_ptr<const Block>>;

std::unique_ptr<Trace> RearrangeBlocks(std::unique_ptr<Trace> trace);

}  // namespace Cg
