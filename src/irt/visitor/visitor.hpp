#pragma once

namespace Irt {

class BinaryOperator;
class Call;
class ConditionalJump;
class Constant;
class ExpressionSequence;
class Jump;
class Label;
class Memory;
class Move;
class Name;
class StatementSequence;
class Temporary;
class Void;

class Visitor {
 public:
  virtual void Visit(BinaryOperator*) = 0;
  virtual void Visit(Call*) = 0;
  virtual void Visit(ConditionalJump*) = 0;
  virtual void Visit(Constant*) = 0;
  virtual void Visit(ExpressionSequence*) = 0;
  virtual void Visit(Jump*) = 0;
  virtual void Visit(Label*) = 0;
  virtual void Visit(Memory*) = 0;
  virtual void Visit(Move*) = 0;
  virtual void Visit(Name*) = 0;
  virtual void Visit(StatementSequence*) = 0;
  virtual void Visit(Temporary*) = 0;
  virtual void Visit(Void*) = 0;
};

}  // namespace Irt
