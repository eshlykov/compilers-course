#pragma once

#include <memory>
#include <string>
#include "../../utils/storage.hpp"
#include "expression.hpp"

namespace Ct {

class Temporary : public Expression {
 public:
  explicit Temporary(Storage storage);

  void Accept(Visitor* visitor) final;

  std::vector<ExpressionPtr> Kids() final;

  ExpressionPtr Build(const std::vector<ExpressionPtr>& expressionList) final;

 public:
  const Storage storage_;
};

inline Temporary::Temporary(Storage storage) : storage_(storage) {}

inline void Temporary::Accept(Visitor* visitor) { visitor->Visit(this); }

inline std::vector<ExpressionPtr> Temporary::Kids() { return {}; }

inline ExpressionPtr Temporary::Build(
    const std::vector<ExpressionPtr>& expressionList) {
  return std::make_shared<Temporary>(storage_);
}

using TemporaryPtr = std::shared_ptr<Temporary>;

}  // namespace Ct
