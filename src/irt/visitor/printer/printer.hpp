#pragma once

#include <fstream>
#include <string>
#include "../../../utils/irt.hpp"
#include "../visitor.hpp"

namespace Irt {

class Printer : public Visitor {
 public:
  explicit Printer(const std::string &filename);

  ~Printer();

  void Visit(BinaryOperator *node) final;

  void Visit(Call *node) final;

  void Visit(ConditionalJump *) final;

  void Visit(Constant *node) final;

  void Visit(ExpressionSequence *) final;

  void Visit(Jump *node) final;

  void Visit(Label *node) final;

  void Visit(Memory *node) final;

  void Visit(Move *node) final;

  void Visit(Name *node) final;

  void Visit(StatementSequence *node) final;

  void Visit(Temporary *node) final;

  void Visit(Void *node) final;

  void Next();

 private:
  void PrintHead(int headNodeNumber, const std::string &label);

  void PrintEdge(int headNodeNumber);

  void PrintLeaf(int headNodeNumber, const std::string &label,
                 const std::string &name);

 private:
  std::ofstream file_;
  int nodeNumber_;
};

}  // namespace Irt
