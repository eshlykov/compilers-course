#include <cg/trace/trace.hpp>

#include <irt/visitor/block-rearrange-visitor.hpp>
#include <irt/visitor/trace-formation-visitor.hpp>

#include <unordered_map>
#include <vector>

using namespace Cg;

std::unique_ptr<Trace> Cg::RearrangeBlocks(std::unique_ptr<Trace> trace) {
  std::unordered_map<std::string, int> blockNameToIndex;
  std::vector<std::string> blockIndexToName;
  std::vector<std::shared_ptr<std::string>> blockIndexToJumpTarget;
  blockIndexToName.reserve(trace->size());
  blockIndexToJumpTarget.reserve(trace->size());
  for (int blockIndex = 0; blockIndex < trace->size(); ++blockIndex) {
    Irt::BlockRearrangeVisitor blockVisitor;

    trace->at(blockIndex)->Accept(&blockVisitor);

    std::string blockName = blockVisitor.LabelName();
    blockNameToIndex.emplace(blockName, blockIndex);
    blockIndexToName.push_back(blockName);

    blockIndexToJumpTarget.push_back(blockVisitor.JumpTargetLabelName());
  }

  std::vector<bool> visited(trace->size(), false);
  std::unique_ptr<Trace> traceArranged(new Trace());
  traceArranged->reserve(trace->size());
  for (int rootBlockIndex = 0; rootBlockIndex < trace->size();
       ++rootBlockIndex) {
    int blockIndex = rootBlockIndex;

    while (blockIndex >= 0 && !visited[blockIndex]) {
      visited[blockIndex] = true;
      auto statementPtr = trace->at(blockIndex)->Clone();
      std::unique_ptr<const Irt::StatementList> blockPtr(
          reinterpret_cast<const Irt::StatementList*>(statementPtr.release()));
      traceArranged->push_back(std::move(blockPtr));
      if (!blockIndexToJumpTarget[blockIndex] ||
          *blockIndexToJumpTarget.at(blockIndex) ==
              Irt::TraceFormationVisitor::EndBlockLabelName()) {
        blockIndex = -1;
      } else {
        blockIndex = blockNameToIndex.at(*blockIndexToJumpTarget[blockIndex]);
      }
    }
  }
  return std::move(traceArranged);
}
