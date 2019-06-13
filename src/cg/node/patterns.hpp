#pragma once

#include <map>
#include <memory>
#include <tuple>

#include <cg/node/commands.hpp>
#include <cg/node/visitor-target.hpp>
#include <irt/node/visitor-target.hpp>

namespace Cg {

using IrtVt = Irt::IVisitorTarget;
using Dynamic =
    std::map<const IrtVt*, std::pair<int, std::unique_ptr<const Command>>>;

class Pattern {
 public:
  explicit Pattern(Dynamic* dynamicVar) : dynamic_(dynamicVar) {}
  virtual ~Pattern() = default;
  virtual void Consume(const IrtVt* node) = 0;

 protected:
  template <typename T>
  class ValidAndValue {
   public:
    ValidAndValue(bool valid, const T& value) : valid_(valid), value_(value) {}
    T operator->() const { return value_; }
    T operator*() const { return value_; }
    bool IsValid() const { return valid_; }

   private:
    bool valid_;
    T value_;
  };

  template <typename Command>
  void ConsumeBinaryOperation(const IrtVt* node, Irt::OperatorTypes operation);

  template <typename T>
  ValidAndValue<const T*> GetTypedNode(const IrtVt* node);
  int GetDynamicPrice(const IrtVt* node);
  const Cg::Expression* GetDynamicValue(const IrtVt* node);

  Dynamic* dynamic_;
};

// Temp pattern
class TempPattern : public Pattern {
 public:
  using Pattern::Pattern;
  void Consume(const IrtVt* node) override;
};

// Label patterns
class LabelPattern : public Pattern {
 public:
  using Pattern::Pattern;
  void Consume(const IrtVt* node) override;
};

// Add Command
// r1 + r2
class AddPattern : public Pattern {
 public:
  using Pattern::Pattern;
  void Consume(const IrtVt* node) override;
};

// Sub command
// r1 - r2
class SubPattern : public Pattern {
 public:
  using Pattern::Pattern;
  void Consume(const IrtVt* node) override;
};

// Mult command
// r1 * r2
class MultPattern : public Pattern {
 public:
  using Pattern::Pattern;
  void Consume(const IrtVt* node) override;
};

// Div command
// r1 / r2
class DivPattern : public Pattern {
 public:
  using Pattern::Pattern;
  void Consume(const IrtVt* node) override;
};

// Sub const command
// r1 - c
class SubConstPattern : public Pattern {
 public:
  using Pattern::Pattern;
  void Consume(const IrtVt* node) override;
};

// Add const commands
// c + r1
class AddConstLeftPattern : public Pattern {
 public:
  using Pattern::Pattern;
  void Consume(const IrtVt* node) override;
};

// r1 + c
class AddConstRightPattern : public Pattern {
 public:
  using Pattern::Pattern;
  void Consume(const IrtVt* node) override;
};

// c
class ConstPattern : public Pattern {
 public:
  using Pattern::Pattern;
  void Consume(const IrtVt* node) override;
};

// Load memory commands
// M[src]
class LoadMemoryPattern : public Pattern {
 public:
  using Pattern::Pattern;
  void Consume(const IrtVt* node) override;
};

// M[C]
class LoadConstMemoryPattern : public Pattern {
 public:
  using Pattern::Pattern;
  void Consume(const IrtVt* node) override;
};

// M[C+src]
class LoadMemoryLeftOffsetPattern : public Pattern {
 public:
  using Pattern::Pattern;
  void Consume(const IrtVt* node) override;
};

// M[src+C]
class LoadMemoryRightOffsetPattern : public Pattern {
 public:
  using Pattern::Pattern;
  void Consume(const IrtVt* node) override;
};

// Store memory commands
// M[dst] = src
class StoreMemoryPattern : public Pattern {
 public:
  using Pattern::Pattern;
  void Consume(const IrtVt* node) override;
};

// M[C] = src
class StoreConstMemoryPattern : public Pattern {
 public:
  using Pattern::Pattern;
  void Consume(const IrtVt* node) override;
};

// M[C+dst] = src
class StoreMemoryLeftOffsetPattern : public Pattern {
 public:
  using Pattern::Pattern;
  void Consume(const IrtVt* node) override;
};

// M[dst + C] = src
class StoreMemoryRightOffsetPattern : public Pattern {
 public:
  using Pattern::Pattern;
  void Consume(const IrtVt* node) override;
};

// TempK = src
class StoreRegisterPattern : public Pattern {
 public:
  using Pattern::Pattern;
  void Consume(const IrtVt* node) override;
};

class CallFunctionPattern : public Pattern {
 public:
  using Pattern::Pattern;
  void Consume(const IrtVt* node) override;
};

class JumpPattern : public Pattern {
 public:
  using Pattern::Pattern;
  void Consume(const IrtVt* node) override;
};

class ConditionalJumpPattern : public Pattern {
 public:
  using Pattern::Pattern;
  void Consume(const IrtVt* node) override;
};

class ExpStatementPattern : public Pattern {
 public:
  using Pattern::Pattern;
  void Consume(const IrtVt* node) override;
};

}  // namespace Cg
